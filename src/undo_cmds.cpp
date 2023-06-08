/////////////////////////////////////////////////////////////////////////////
// Purpose:   Undoable command classes derived from UndoAction
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <set>

#include <wx/wupdlock.h>  // wxWindowUpdateLocker prevents window redrawing

#include "undo_cmds.h"

#include "../panels/nav_panel.h"  // NavigationPanel -- Navigation Panel
#include "mainframe.h"            // MainFrame -- Main window frame
#include "node.h"                 // Node class
#include "node_creator.h"         // NodeCreator -- Class used to create nodes
#include "node_gridbag.h"         // GridBag -- Create and modify a node containing a wxGridBagSizer
#include "project_handler.h"      // ProjectHandler class
#include "utils.h"                // Utility functions that work with properties

#include "generate/images_form.h"  // Needed for GatherImages() declaration

///////////////////////////////// InsertNodeAction ////////////////////////////////////

InsertNodeAction::InsertNodeAction(Node* node, Node* parent, const tt_string& undo_str, int pos)
{
    Init(node->GetSharedPtr(), parent->GetSharedPtr(), undo_str, pos);
}

InsertNodeAction::InsertNodeAction(const NodeSharedPtr node, const NodeSharedPtr parent, tt_string_view undo_str, int pos)
{
    Init(node, parent, undo_str, pos);
}

void InsertNodeAction::Init(const NodeSharedPtr node, const NodeSharedPtr parent, tt_string_view undo_str, int pos)
{
    m_old_selected = wxGetFrame().GetSelectedNodePtr();
    m_node = node;
    m_parent = parent;
    SetUndoString(undo_str);
    m_pos = pos;

    if (m_node->isGen(gen_folder) || m_node->isGen(gen_sub_folder))
    {
        m_fix_duplicate_names = false;
    }
}

void InsertNodeAction::Change()
{
    m_node->SetParent(m_parent);

    ASSERT_MSG(!m_parent->isGen(gen_wxGridBagSizer), "Only use AppendGridBagAction to add items to a wxGridBagSizer!");

    if (m_pos == -1 && m_parent->IsSizer() && m_parent->GetChildCount() > 0 &&
        m_parent->GetChildPtr(m_parent->GetChildCount() - 1)->isGen(gen_wxStdDialogButtonSizer))
    {
        m_parent->AddChild(m_node);
        // Add the child BEFORE any wxStdDialogButtonSizer
        m_parent->ChangeChildPosition(m_node, m_parent->GetChildCount() - 2);
    }
    else if (m_parent->isGen(gen_Images) && m_parent->as_bool(prop_auto_update))
    {
        m_pos = 0;
        for (const auto& embedded_image: m_parent->GetChildNodePtrs())
        {
            if (CompareImageNames(m_node, embedded_image))
                break;
            ++m_pos;
        }
        m_parent->AddChild(m_node);
        if (m_pos <  (to_int) m_parent->GetChildCount())
            m_parent->ChangeChildPosition(m_node, m_pos);
    }
    else
    {
        m_parent->AddChild(m_node);
        if (m_pos >= 0)
            m_parent->ChangeChildPosition(m_node, m_pos);
    }

    if (m_fix_duplicate_names)
    {
        // This needs to be done only once, even if the insertion is reverted and then changed again. The reason is that any
        // name changes to other nodes cannot be undone.

        m_node->FixDuplicateNodeNames();
        m_fix_duplicate_names = false;
    }

    if (m_fire_created_event)
    {
        wxGetFrame().FireCreatedEvent(m_node.get());
    }

    // Probably not necessary, but with both parameters set to false, this simply ensures the mainframe has it's selection
    // node set correctly.
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node.get(), evt_flags::no_event);
}

void InsertNodeAction::Revert()
{
    m_parent->RemoveChild(m_node);
    m_node->SetParent(NodeSharedPtr());  // Remove the parent pointer
    if (m_fire_created_event)
    {
        wxGetFrame().FireDeletedEvent(m_node.get());
    }
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_old_selected.get());
}

///////////////////////////////// RemoveNodeAction ////////////////////////////////////

RemoveNodeAction::RemoveNodeAction(Node* node, const tt_string& undo_str, bool AddToClipboard)
{
    Init(node->GetSharedPtr(), undo_str, AddToClipboard);
}

RemoveNodeAction::RemoveNodeAction(const NodeSharedPtr node, const tt_string& undo_str, bool AddToClipboard)
{
    Init(node, undo_str, AddToClipboard);
}

void RemoveNodeAction::Init(const NodeSharedPtr node, tt_string_view undo_str, bool AddToClipboard)
{
    m_AddToClipboard = AddToClipboard;
    m_node = node;
    m_parent = node->GetParentPtr();
    m_old_pos = m_parent->GetChildPosition(node);
    m_old_selected = wxGetFrame().GetSelectedNodePtr();
    SetUndoString(undo_str);

    m_RedoEventGenerated = true;
    m_RedoSelectEventGenerated = true;

}

void RemoveNodeAction::Change()
{
    if (m_AddToClipboard)
        wxGetFrame().CopyNode(m_node.get());

    m_parent->RemoveChild(m_node);
    m_node->SetParent(NodeSharedPtr());

    wxGetFrame().FireDeletedEvent(m_node.get());

    if (m_parent->GetChildCount())
    {
        auto pos = (m_old_pos < m_parent->GetChildCount() ? m_old_pos : m_parent->GetChildCount() - 1);
        if (isAllowedSelectEvent())
            wxGetFrame().SelectNode(m_parent->GetChild(pos));
    }
    else
    {
        if (isAllowedSelectEvent())
            wxGetFrame().SelectNode(m_parent.get());
    }
}

void RemoveNodeAction::Revert()
{
    m_parent->AddChild(m_node);
    m_node->SetParent(m_parent);
    m_parent->ChangeChildPosition(m_node, m_old_pos);

    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_old_selected.get(), evt_flags::force_selection);
}

///////////////////////////////// ModifyPropertyAction ////////////////////////////////////

ModifyPropertyAction::ModifyPropertyAction(NodeProperty* prop, tt_string_view value) : m_property(prop)
{
    m_undo_string << "change " << prop->DeclName();

    m_change_value << value;
    m_revert_value = prop->as_string();
    m_RedoEventGenerated = true;
    m_UndoEventGenerated = true;
}

ModifyPropertyAction::ModifyPropertyAction(NodeProperty* prop, int value) : m_property(prop)
{
    m_undo_string << "change " << prop->DeclName();

    m_change_value << value;
    m_revert_value = prop->as_string();
}

void ModifyPropertyAction::Change()
{
    m_property->set_value(m_change_value);

    wxGetFrame().FirePropChangeEvent(m_property);
}

void ModifyPropertyAction::Revert()
{
    m_property->set_value(m_revert_value);

    wxGetFrame().FirePropChangeEvent(m_property);
}

///////////////////////////////// ModifyProperties ////////////////////////////////////

ModifyProperties::ModifyProperties(tt_string_view undo_string, bool fire_events) : UndoAction(undo_string)
{
    m_fire_events = fire_events;
    m_RedoEventGenerated = true;
    m_UndoEventGenerated = true;
}

void ModifyProperties::AddProperty(NodeProperty* prop, tt_string_view value)
{
    auto& entry = m_properties.emplace_back();
    entry.property = prop;
    entry.change_value = value;
    entry.revert_value = prop->as_string();
}

void ModifyProperties::AddProperty(NodeProperty* prop, int value)
{
    auto& entry = m_properties.emplace_back();
    entry.property = prop;
    entry.change_value << value;
    entry.revert_value = prop->as_string();
}

void ModifyProperties::Change()
{
    for (auto& iter: m_properties)
    {
        iter.property->set_value(iter.change_value);
    }

    if (m_fire_events)
        wxGetFrame().FireMultiPropEvent(this);
}

void ModifyProperties::Revert()
{
    for (auto& iter: m_properties)
    {
        iter.property->set_value(iter.revert_value);
    }

    if (m_fire_events)
        wxGetFrame().FireMultiPropEvent(this);
}

///////////////////////////////// ModifyEventAction ////////////////////////////////////

ModifyEventAction::ModifyEventAction(NodeEvent* event, tt_string_view value) : m_event(event), m_change_value(value)
{
    m_undo_string << "change " << event->get_name() << " handler";

    m_revert_value = event->get_value();

    m_RedoEventGenerated = true;
    m_UndoEventGenerated = true;
}

void ModifyEventAction::Change()
{
    m_event->set_value(m_change_value);
    wxGetFrame().FireChangeEventHandler(m_event);
}

void ModifyEventAction::Revert()
{
    m_event->set_value(m_revert_value);
    wxGetFrame().FireChangeEventHandler(m_event);
}

///////////////////////////////// ChangePositionAction ////////////////////////////////////

ChangePositionAction::ChangePositionAction(Node* node, size_t position)
{
    Init(node->GetSharedPtr(), position);
}

ChangePositionAction::ChangePositionAction(const NodeSharedPtr node, size_t position)
{
    Init(node, position);
}

void ChangePositionAction::Init(const NodeSharedPtr node, size_t position)
{
    m_node = node;
    m_parent = node->GetParentPtr();

    m_change_pos = position;
    m_revert_pos = m_parent->GetChildPosition(node);

    SetUndoString(tt_string() << "change " << node->DeclName() << " position");

    m_UndoEventGenerated = true;
    m_RedoEventGenerated = true;
    m_UndoSelectEventGenerated = true;
    m_RedoSelectEventGenerated = true;
}

void ChangePositionAction::Change()
{
    m_parent->ChangeChildPosition(m_node, m_change_pos);
    wxGetFrame().FirePositionChangedEvent(this);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node);
}

void ChangePositionAction::Revert()
{
    m_parent->ChangeChildPosition(m_node, m_revert_pos);
    wxGetFrame().FirePositionChangedEvent(this);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node);
}

///////////////////////////////// ChangeSizerType ////////////////////////////////////

ChangeSizerType::ChangeSizerType(Node* node, GenEnum::GenName new_gen_sizer)
{
    m_undo_string << "change sizer type";

    m_old_node = node->GetSharedPtr();
    m_parent = node->GetParentPtr();
    m_new_gen_sizer = new_gen_sizer;

    m_node = NodeCreation.NewNode(m_new_gen_sizer);
    ASSERT(m_node);
    if (m_node)
    {
        if (m_new_gen_sizer == gen_wxFlexGridSizer &&
            (m_old_node->isGen(gen_wxBoxSizer) || m_old_node->isGen(gen_VerticalBoxSizer)))
        {
            if (m_old_node->prop_as_string(prop_orientation) == "wxHORIZONTAL")
            {
                m_node->prop_set_value(prop_cols, (to_int) m_old_node->GetChildCount());
            }
            else
            {
                m_node->prop_set_value(prop_cols, 0);
                m_node->prop_set_value(prop_rows, (to_int) m_old_node->GetChildCount());
            }
        }

        for (const auto& iter: m_old_node->GetChildNodePtrs())
        {
            m_node->Adopt(NodeCreation.MakeCopy(iter.get()));
        }
    }
}

void ChangeSizerType::Change()
{
    auto pos = m_parent->GetChildPosition(m_old_node.get());
    m_parent->RemoveChild(m_old_node);
    m_old_node->SetParent(NodeSharedPtr());
    m_parent->Adopt(m_node);
    if (auto parent_form = m_parent->get_form(); parent_form)
    {
        parent_form->FixDuplicateNodeNames();
    }
    m_parent->ChangeChildPosition(m_node, pos);

    wxGetFrame().FireDeletedEvent(m_old_node.get());
    wxGetFrame().FireCreatedEvent(m_node);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node.get());
    wxGetFrame().GetNavigationPanel()->ChangeExpansion(m_node.get(), true, true);
}

void ChangeSizerType::Revert()
{
    auto pos = m_parent->GetChildPosition(m_node.get());
    m_parent->RemoveChild(m_node);
    m_node->SetParent(NodeSharedPtr());
    m_parent->Adopt(m_old_node);
    m_parent->ChangeChildPosition(m_old_node, pos);

    wxGetFrame().FireDeletedEvent(m_node.get());
    wxGetFrame().FireCreatedEvent(m_old_node);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_old_node.get());
}

///////////////////////////////// ChangeNodeType ////////////////////////////////////

static auto lst_common_properties = {

    prop_alignment,
    prop_background_colour,
    prop_border_size,
    prop_borders,
    prop_class_access,
    prop_disabled,
    prop_flags,
    prop_font,
    prop_foreground_colour,
    prop_hidden,
    prop_hint,
    prop_label,
    prop_max_size,
    prop_min_size,
    prop_platforms,
    prop_pos,
    prop_proportion,
    prop_size,
    prop_tooltip,
    prop_var_comment,
    prop_variant,
    prop_window_extra_style,
    prop_window_style,
    prop_contents,
    prop_selection_string,
    prop_selection_int,

    prop_validator_variable,
    prop_validator_data_type,
    prop_validator_type,
    prop_validator_style,
    prop_get_function,
    prop_set_function,

};

static void CopyCommonProperties(Node* old_node, Node* new_node)
{
    for (auto prop: lst_common_properties)
    {
        if (new_node->HasProp(prop) && old_node->HasProp(prop))
        {
            new_node->prop_set_value(prop, old_node->prop_as_string(prop));
        }
    }
}

ChangeNodeType::ChangeNodeType(Node* node, GenEnum::GenName new_node)
{
    m_undo_string << "change widget type";

    m_old_node = node->GetSharedPtr();
    m_parent = node->GetParentPtr();
    m_new_gen_node = new_node;

    m_node = NodeCreation.NewNode(m_new_gen_node);
    ASSERT(m_node);
    if (m_node)
    {
        CopyCommonProperties(m_old_node.get(), m_node.get());
        if (m_new_gen_node == gen_wxCheckBox || m_new_gen_node == gen_wxRadioBox)
        {
            m_node->prop_set_value(prop_checked, m_old_node->prop_as_bool(prop_checked));
        }

        for (const auto& iter: m_old_node->GetChildNodePtrs())
        {
            m_node->Adopt(NodeCreation.MakeCopy(iter.get()));
        }
    }
}

void ChangeNodeType::Change()
{
    auto pos = m_parent->GetChildPosition(m_old_node.get());
    m_parent->RemoveChild(m_old_node);
    m_old_node->SetParent(NodeSharedPtr());
    m_parent->Adopt(m_node);
    if (auto parent_form = m_parent->get_form(); parent_form)
    {
        parent_form->FixDuplicateNodeNames();
    }
    m_parent->ChangeChildPosition(m_node, pos);

    wxGetFrame().FireDeletedEvent(m_old_node.get());
    wxGetFrame().FireCreatedEvent(m_node);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node.get());
    wxGetFrame().GetNavigationPanel()->ChangeExpansion(m_node.get(), true, true);
}

void ChangeNodeType::Revert()
{
    auto pos = m_parent->GetChildPosition(m_node.get());
    m_parent->RemoveChild(m_node);
    m_node->SetParent(NodeSharedPtr());
    m_parent->Adopt(m_old_node);
    m_parent->ChangeChildPosition(m_old_node, pos);

    wxGetFrame().FireDeletedEvent(m_node.get());
    wxGetFrame().FireCreatedEvent(m_old_node);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_old_node.get());
}

///////////////////////////////// ChangeParentAction ////////////////////////////////////

ChangeParentAction::ChangeParentAction(Node* node, Node* parent)
{
    Init(node->GetSharedPtr(), parent->GetSharedPtr());
}

ChangeParentAction::ChangeParentAction(const NodeSharedPtr node, const NodeSharedPtr parent)
{
    Init(node, parent);
}

void ChangeParentAction::Init(const NodeSharedPtr node, const NodeSharedPtr parent)
{
    m_node = node;
    m_change_parent = parent;
    m_revert_parent = node->GetParentPtr();

    m_revert_position = m_revert_parent->GetChildPosition(node.get());
    m_revert_row = node->prop_as_int(prop_row);
    m_revert_col = node->prop_as_int(prop_column);

    SetUndoString(tt_string()  << "change " << node->DeclName() << " parent");

    m_UndoEventGenerated = true;
    m_RedoEventGenerated = true;
    m_UndoSelectEventGenerated = true;
    m_RedoSelectEventGenerated = true;
}

void ChangeParentAction::Change()
{
    m_revert_parent->RemoveChild(m_node);
    wxGetFrame().GetNavigationPanel()->DeleteNode(m_node.get());
    if (m_change_parent->isGen(gen_wxGridBagSizer))
    {
        GridBag grid_bag(m_change_parent.get());
        if (!grid_bag.InsertNode(m_change_parent.get(), m_node.get()))
        {
            m_node->SetParent(m_revert_parent);
            m_revert_parent->AddChild(m_node);
            m_revert_parent->ChangeChildPosition(m_node, m_revert_position);
            // Since we deleted it from Navigation Panel, need to add it back
            wxGetFrame().FireParentChangedEvent(this);
            if (isAllowedSelectEvent())
                wxGetFrame().SelectNode(m_node);
        }
    }
    else if (m_change_parent->AddChild(m_node))
    {
        m_node->SetParent(m_change_parent);

        wxGetFrame().FireParentChangedEvent(this);
        if (isAllowedSelectEvent())
            wxGetFrame().SelectNode(m_node);
    }
}

void ChangeParentAction::Revert()
{
    m_change_parent->RemoveChild(m_node);

    m_node->SetParent(m_revert_parent);
    m_revert_parent->AddChild(m_node);
    m_revert_parent->ChangeChildPosition(m_node, m_revert_position);
    if (auto prop = m_node->get_prop_ptr(prop_row); prop)
        prop->set_value(m_revert_row);
    if (auto prop = m_node->get_prop_ptr(prop_column); prop)
        prop->set_value(m_revert_col);

    wxGetFrame().FireParentChangedEvent(this);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node);
}

///////////////////////////////// AppendGridBagAction ////////////////////////////////////

AppendGridBagAction::AppendGridBagAction(Node* node, Node* parent, int pos) : m_pos(pos)
{
    m_old_selected = wxGetFrame().GetSelectedNodePtr();
    m_node = node->GetSharedPtr();
    m_parent = parent->GetSharedPtr();
    m_old_pos = m_parent->GetChildPosition(node);

    m_undo_string << "Append " << map_GenNames[node->gen_name()];

    m_RedoEventGenerated = true;
    m_RedoSelectEventGenerated = true;
    m_UndoEventGenerated = true;
    m_UndoSelectEventGenerated = true;
}

void AppendGridBagAction::Change()
{
    m_node->SetParent(m_parent);
    if (m_pos == -1 && m_parent->GetChildCount() > 0 &&
        m_parent->GetChildPtr(m_parent->GetChildCount() - 1)->isGen(gen_wxStdDialogButtonSizer))
    {
        m_parent->AddChild(m_node);
        m_parent->ChangeChildPosition(m_node, m_parent->GetChildCount() - 2);
    }
    else
    {
        m_parent->AddChild(m_node);
        if (m_pos >= 0)
            m_parent->ChangeChildPosition(m_node, m_pos);
    }

    if (m_fix_duplicate_names)
    {
        // This needs to be done only once, even if the insertion is reverted and then changed again. The reason is that
        // any name changes to other nodes cannot be undone.

        m_node->FixDuplicateNodeNames();
        m_fix_duplicate_names = false;
    }

    wxGetFrame().FireCreatedEvent(m_node);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node, evt_flags::fire_event | evt_flags::force_selection);
}

void AppendGridBagAction::Revert()
{
    m_parent->RemoveChild(m_node);
    m_node->SetParent(NodeSharedPtr());

    wxGetFrame().FireDeletedEvent(m_node.get());
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_old_selected.get());
}

///////////////////////////////// GridBagAction ////////////////////////////////////

GridBagAction::GridBagAction(Node* cur_gbsizer, const tt_string& undo_str) : UndoAction(undo_str.c_str())
{
    m_RedoEventGenerated = true;
    m_RedoSelectEventGenerated = true;
    m_UndoEventGenerated = true;
    m_UndoSelectEventGenerated = true;

    m_cur_gbsizer = cur_gbsizer->GetSharedPtr();
    m_old_gbsizer = NodeCreation.MakeCopy(cur_gbsizer);

    auto nav_panel = wxGetFrame().GetNavigationPanel();

    // Thaw() is called when GridBagAction::Update() is called
    nav_panel->Freeze();

    for (const auto& child: cur_gbsizer->GetChildNodePtrs())
    {
        nav_panel->EraseAllMaps(child.get());
    }
}

void GridBagAction::Change()
{
    if (m_isReverted)
    {
        auto nav_panel = wxGetFrame().GetNavigationPanel();
        wxWindowUpdateLocker freeze(nav_panel);

        for (const auto& child: m_cur_gbsizer->GetChildNodePtrs())
        {
            nav_panel->EraseAllMaps(child.get());
        }

        auto save = NodeCreation.MakeCopy(m_cur_gbsizer);
        m_cur_gbsizer->RemoveAllChildren();

        for (const auto& child: m_old_gbsizer->GetChildNodePtrs())
        {
            m_cur_gbsizer->Adopt(NodeCreation.MakeCopy(child.get()));
        }
        m_old_gbsizer = std::move(save);
        m_isReverted = false;

        nav_panel->AddAllChildren(m_cur_gbsizer.get());
        nav_panel->ExpandAllNodes(m_cur_gbsizer.get());

        wxGetFrame().FireGridBagActionEvent(this);
        if (isAllowedSelectEvent())
            wxGetFrame().SelectNode(m_cur_gbsizer);
    }
}

void GridBagAction::Revert()
{
    auto nav_panel = wxGetFrame().GetNavigationPanel();
    wxWindowUpdateLocker freeze(nav_panel);

    for (const auto& child: m_cur_gbsizer->GetChildNodePtrs())
    {
        nav_panel->EraseAllMaps(child.get());
    }

    auto save = NodeCreation.MakeCopy(m_cur_gbsizer);
    m_cur_gbsizer->RemoveAllChildren();
    for (const auto& child: m_old_gbsizer->GetChildNodePtrs())
    {
        m_cur_gbsizer->Adopt(NodeCreation.MakeCopy(child.get()));
    }
    m_old_gbsizer = std::move(save);
    m_isReverted = true;

    nav_panel->AddAllChildren(m_cur_gbsizer.get());
    nav_panel->ExpandAllNodes(m_cur_gbsizer.get());

    wxGetFrame().FireGridBagActionEvent(this);
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_cur_gbsizer);
}

void GridBagAction::Update()
{
    auto nav_panel = wxGetFrame().GetNavigationPanel();

    for (const auto& child: m_cur_gbsizer->GetChildNodePtrs())
    {
        nav_panel->EraseAllMaps(child.get());
    }

    nav_panel->AddAllChildren(m_cur_gbsizer.get());
    nav_panel->ExpandAllNodes(m_cur_gbsizer.get());
    nav_panel->Thaw();
}

///////////////////////////////// SortProjectAction ////////////////////////////////////

static bool CompareClassNames(NodeSharedPtr a, NodeSharedPtr b)
{
    // Sort folders first, then forms
    if (a->isGen(gen_folder) && !b->isGen(gen_folder))
        return true;
    else if (a->isGen(gen_folder) && b->isGen(gen_folder))
        return (a->prop_as_string(prop_label).compare(b->prop_as_string(prop_label)) < 0);
    else if (a->isGen(gen_sub_folder) && !b->isGen(gen_sub_folder))
        return true;
    else if (a->isGen(gen_sub_folder) && b->isGen(gen_sub_folder))
        return (a->prop_as_string(prop_label).compare(b->prop_as_string(prop_label)) < 0);
    return (a->prop_as_string(prop_class_name).compare(b->prop_as_string(prop_class_name)) < 0);
}

SortProjectAction::SortProjectAction()
{
    m_RedoEventGenerated = true;
    m_RedoSelectEventGenerated = true;
    m_UndoEventGenerated = true;
    m_UndoSelectEventGenerated = true;

    m_undo_string = "Sort Project";

    m_old_project = NodeCreation.MakeCopy(Project.ProjectNode());
}

void SortProjectAction::Change()
{
    m_old_project = NodeCreation.MakeCopy(Project.ProjectNode());

    auto& children = Project.ChildNodePtrs();
    std::sort(children.begin(), children.end(), CompareClassNames);

    for (auto& iter: Project.ChildNodePtrs())
    {
        if (iter->isGen(gen_folder))
        {
            SortFolder(iter.get());
        }
    }

    wxGetFrame().FireProjectUpdatedEvent();
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(Project.ProjectNode());
}

void SortProjectAction::SortFolder(Node* folder)
{
    auto& children = folder->GetChildNodePtrs();
    std::sort(children.begin(), children.end(), CompareClassNames);

    for (auto& iter: folder->GetChildNodePtrs())
    {
        if (iter->isGen(gen_sub_folder))
        {
            SortFolder(iter.get());
        }
    }
}

void SortProjectAction::Revert()
{
    Project.ProjectNode()->RemoveAllChildren();
    for (const auto& child: m_old_project->GetChildNodePtrs())
    {
        Project.ProjectNode()->Adopt(NodeCreation.MakeCopy(child.get()));
    }

    wxGetFrame().FireProjectUpdatedEvent();
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(Project.ProjectNode());
}

///////////////////////////////// SortImagesAction ////////////////////////////////////

const char* txt_sort_images_undo_string = "Sort Images";

SortImagesAction::SortImagesAction(Node* node)
{
    m_node = node->GetSharedPtr();
    m_parent = node->GetParentPtr();
    m_old_pos = m_parent->GetChildPosition(node);

    m_RedoEventGenerated = true;
    m_UndoEventGenerated = true;

    m_undo_string = txt_sort_images_undo_string;
}

void SortImagesAction::Change()
{
    m_old_images = NodeCreation.MakeCopy(m_node);

    auto& children = m_node->GetChildNodePtrs();
    std::sort(children.begin(), children.end(), CompareImageNames);
    m_node->set_value(prop_sorted, true);

    wxGetFrame().GetNavigationPanel()->RefreshParent(m_node.get());
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node);
    wxGetFrame().FirePropChangeEvent(m_node->get_prop_ptr(prop_sorted));
}

void SortImagesAction::Revert()
{
    auto nav_panel = wxGetFrame().GetNavigationPanel();
    wxWindowUpdateLocker freeze(nav_panel);

    for (const auto& child: m_node->GetChildNodePtrs())
    {
        nav_panel->EraseAllMaps(child.get());
    }

    m_node->RemoveAllChildren();

    for (const auto& child: m_old_images->GetChildNodePtrs())
    {
        m_node->Adopt(child);
    }
    m_node->set_value(prop_sorted, false);
    m_old_images.reset();

    nav_panel->AddAllChildren(m_node.get());
    if (isAllowedSelectEvent())
        wxGetFrame().SelectNode(m_node);
    wxGetFrame().FirePropChangeEvent(m_node->get_prop_ptr(prop_sorted));
}

///////////////////////////////// AutoImagesAction ////////////////////////////////////

const char* txt_update_images_undo_string = "Update Images";

AutoImagesAction::AutoImagesAction(Node* node)
{
    m_node = node->GetSharedPtr();
    m_parent = node->GetParentPtr();
    m_old_pos = m_parent->GetChildPosition(node);

    m_RedoEventGenerated = true;
    m_UndoEventGenerated = true;

    m_undo_string = txt_update_images_undo_string;

    // This should either be a folder or a project
    ASSERT(m_parent->isGen(gen_folder) || m_parent->isGen(gen_Project));

    std::set<std::string> image_names;
    for (auto& iter: m_node->GetChildNodePtrs())
    {
        image_names.insert(iter->value(prop_bitmap));
    }

    std::vector<std::string> new_images;
    for (auto& child: m_parent->GetChildNodePtrs())
    {
        // Note that GatherImages will update both image_names and new_images
        GatherImages(child.get(), image_names, new_images);
    }

    if (new_images.size())
    {
        for (auto& iter: new_images)
        {
            auto new_node = NodeCreation.CreateNode(gen_embedded_image, m_node.get());
            new_node->set_value(prop_bitmap, iter);
            auto insert_action = std::make_shared<InsertNodeAction>(new_node.get(), m_node.get(), tt_empty_cstr);
            insert_action->AllowSelectEvent(false);
            insert_action->SetFireCreatedEvent(true);
            m_actions.push_back(insert_action);
        }
    }

    auto prop_action = std::make_shared<ModifyPropertyAction>(m_node->get_prop_ptr(prop_auto_update), true);
    prop_action->AllowSelectEvent(false);
    m_actions.push_back(prop_action);
}

void AutoImagesAction::Change()
{
    for (auto& iter: m_actions)
    {
        iter->Change();
    }
    wxGetFrame().SelectNode(m_node);
}

void AutoImagesAction::Revert()
{
    auto nav_panel = wxGetFrame().GetNavigationPanel();
    wxWindowUpdateLocker freeze(nav_panel);

#if 0
    for (const auto& child: m_node->GetChildNodePtrs())
    {
        nav_panel->EraseAllMaps(child.get());
    }
#endif

    for (auto& iter: m_actions)
    {
        iter->Revert();
    }

    // nav_panel->AddAllChildren(m_node.get());

    wxGetFrame().SelectNode(m_node);
}
