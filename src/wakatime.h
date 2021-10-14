/////////////////////////////////////////////////////////////////////////////
// Purpose:   Updates WakaTime metrics
// Author:    Ralph Walden
// Copyright: Copyright (c) 2021 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

class WakaTime
{
public:
    WakaTime();

    void SendHeartbeat(bool FileSavedEvent = false);

    static bool IsWakaTimeAvailable();

protected:
    // Caution: It's possible that this function will fail and m_waka_cli will be empty.
    void SetWakaExePath();

private:
    ttlib::cstr m_waka_cli;
    intmax_t m_last_heartbeat { 0 };  // last second tick
};
