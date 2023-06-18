/////////////////////////////////////////////////////////////////////////////
// Purpose:   std::string with additional methods
// Author:    Ralph Walden
// Copyright: Copyright (c) 2020-2023 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once  // NOLINT(#pragma once in main file)

#if !(__cplusplus >= 201703L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L))
    #error "The contents of <tt_string.h> are available only with C++17 or later."
#endif

#include <filesystem>

#include "tt.h"  // tt namespace functions and declarations

#include "tt_string_view.h"  // tt_string_view -- std::string_view with additional methods

// std::string with additional methods.
//
// On Windows, std::wstring/wstring_view is assumed to be UTF16 and is automatically
// converted to UTF8 in constructors and assignments.
class tt_string : public std::basic_string<char, std::char_traits<char>, std::allocator<char>>
{
    using std_base = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

public:
    tt_string(void) { assign(tt::emptystring); }
    tt_string(const char* psz) { assign(psz); }
    tt_string(std::string_view view) : std_base(view) {}
    tt_string(const tt_string& str) : std_base(str) {}
    tt_string(const std::string& str) : std_base(str) {}

    tt_string(const std::filesystem::directory_entry& dir) : std_base(dir.path().string(), dir.path().string().size()) {}

    tt_string(const wxString& str) { *this = str.utf8_string(); }

    tt_string& from_utf16(std::wstring_view str)
    {
        clear();
        tt::utf16to8(str, *this);
        return *this;
    }
    std::wstring to_utf16() const;
    std::wstring as_utf16() const { return to_utf16(); };

    tt_string& utf(std::wstring_view str)
    {
        clear();
        tt::utf16to8(str, *this);
        return *this;
    }

    tt_string& utf(std::string_view str)
    {
        *this = str;
        return *this;
    }

    // FromUTF8() is very efficient if wxUSE_UNICODE_UTF8 is defined as no UTF conversion is
    // done.
    wxString make_wxString() const { return wxString::FromUTF8(data(), size()); }

// If on Windows, and not a wxUSE_UNICODE_UTF8 build, return value converts to UTF16
#if defined(_WIN32) && !(wxUSE_UNICODE_UTF8)
    std::wstring wx_str() const { return to_utf16(); };
#else
    std::string wx_str() const { return substr(); }
#endif  // _WIN32

    // Caution: std::string_view will be invalid if tt_string is modified or destroyed.
    tt_string_view subview(size_t start = 0) const;

    // Case-insensitive comparison.
    int comparei(std::string_view str) const;

    // Locates the position of a substring.
    size_t locate(std::string_view str, size_t posStart = 0, tt::CASE check = tt::CASE::exact) const;

#if ((__cplusplus > 202002L || (defined(_MSVC_LANG) && _MSVC_LANG > 202002L)) && defined(__cpp_lib_string_contains))
    // C++23 already has a contains() function, so we just declare our variation that supports
    // case-insensitive (normal and utf8).

    // Returns true if the sub string exists
    bool contains(std::string_view sub, tt::CASE checkcase) const { return (locate(sub, 0, checkcase) != npos); }
#else
    // Returns true if the sub string exists
    bool contains(std::string_view sub, tt::CASE checkcase = tt::CASE::exact) const
    {
        return (locate(sub, 0, checkcase) != npos);
    }
#endif

    // Returns true if any string in the iteration list appears somewhere in the the main string.
    template <class iterT>
    bool strContains(iterT iter, tt::CASE checkcase = tt::CASE::exact)
    {
        for (auto& strIter: iter)
        {
            if (contains(strIter, checkcase))
                return true;
        }
        return false;
    }

    // Find any one of the characters in a set. Returns offset if found, npos if not.
    //
    // This is equivalent to calling std::strpbrk but returns an offset instead of a pointer.
    size_t find_oneof(const char* pszSet) const;

    // Find any one of the characters in a set. Returns offset if found, npos if not.
    //
    // This is equivalent to calling std::strpbrk but returns an offset instead of a pointer.
    size_t find_oneof(const char* set, size_t start) const;

    // Returns offset to the next whitespace character starting with pos. Returns npos if
    // there are no more whitespaces.
    //
    // A whitespace character is a space, tab, eol or form feed character.
    size_t find_space(size_t start = 0) const;
    tt_string_view view_space(size_t start = 0) const;

    // Returns offset to the next non-whitespace character starting with pos. Returns npos
    // if there are no more non-whitespace characters.
    //
    // A whitespace character is a space, tab, eol or form feed character.
    size_t find_nonspace(size_t start = 0) const;
    tt_string_view view_nonspace(size_t start = 0) const;

    // Returns an offset to the next word -- i.e., find the first non-whitedspace character
    // after the next whitespace character.
    //
    // Equivalent to find_nonspace(find_space(start)).
    size_t stepover(size_t start = 0) const;
    tt_string_view view_stepover(size_t start = 0) const;

    // Returns true if the sub-string is identical to the first part of the main string
    bool is_sameas(std::string_view str, tt::CASE checkcase = tt::CASE::exact) const;

    // Returns true if the sub-string is identical to the first part of the main string
    bool is_sameprefix(std::string_view str, tt::CASE checkcase = tt::CASE::exact) const;

    int atoi(size_t start = 0) const { return tt::atoi(c_str() + start); }

    // If character is found, line is truncated from the character on, and then
    // any trailing space is removed.
    void erase_from(char ch);

    // If string is found, line is truncated from the string on, and then
    // any trailing space is removed.
    void erase_from(std::string_view sub);

    // Removes whitespace: ' ', \t, \r, \\n, \f
    //
    // where: TRIM::right, TRIM::left, or TRIM::both
    tt_string& trim(tt::TRIM where = tt::TRIM::right);

    // Remove locale-dependent whitespace from right side
    inline void RightTrim()
    {
        erase(std::find_if(rbegin(), rend(),
                           [](unsigned char ch)
                           {
                               return !std::isspace(ch);
                           })
                  .base(),
              end());
    }

    // Remove locale-dependent whitespace from left side
    inline void LeftTrim()
    {
        erase(begin(), std::find_if(begin(), end(),
                                    [](unsigned char ch)
                                    {
                                        return !std::isspace(ch);
                                    }));
    }

    // Remove locale-dependent whitespace from left and right side
    inline void BothTrim()
    {
        LeftTrim();
        RightTrim();
    }

    // Returns a view of the characters between chBegin and chEnd. This is typically used
    // to view the contents of a quoted string. Returns the position of the ending
    //  character in src.
    //
    // Unless chBegin is a whitespace character, all whitespace characters starting with
    // offset will be ignored.
    tt_string_view view_substr(size_t offset, char chBegin = '"', char chEnd = '"');

    // Assigns the string between chBegin and chEnd. This is typically used to copy the
    // contents of a quoted string. Returns the position of the ending character in src.
    //
    // Unless chBegin is a whitespace character, all whitespace characters starting with
    // offset will be ignored.
    size_t AssignSubString(std::string_view src, char chBegin = '"', char chEnd = '"');

    // Extracts a string from another string using start and end characters deduced from
    // the first non-whitespace character after offset. Supports double and single quotes,
    // angle and square brackets, and parenthesis.
    //
    // The return position is to the character in src that ended the string, or **npos** if no
    // ending character was found.
    size_t ExtractSubString(std::string_view src, size_t offset = 0);

    // Identical to ExtractSubString only it returns tt_string& instead of a size_t
    tt_string& CreateSubString(std::string_view src, size_t offset = 0)
    {
        ExtractSubString(src, offset);
        return *this;
    }

    // Replace first (or all) occurrences of substring with another one
    size_t Replace(std::string_view oldtext, std::string_view newtext, bool replace_all = tt::REPLACE::once,
                   tt::CASE checkcase = tt::CASE::exact);

    // Replace everything from pos to the end of the current string with str
    tt_string& replace_all(size_t pos, std::string_view str)
    {
        replace(pos, length() - pos, str);
        return *this;
    }

    // Generates hash of current string using djb2 hash algorithm
    size_t get_hash() const noexcept;

    // Convert the entire string to lower case. Assumes the string is UTF8.
    tt_string& MakeLower();

    // Convert the entire string to upper case. Assumes the string is UTF8.
    tt_string& MakeUpper();

    // Assign the specified environment variable, returning true if found.
    //
    // Current string is replaced if found, cleared if not.
    bool assignEnvVar(const char* env_var);

    // Similer to sprintf, but without floating point support.
    //
    // %k flag will place a string argument in quotes, and format a numerical argument
    // with commas or periods (depending on the current locale).
    //
    // %z is considered unsigned unless the value is -1.
    tt_string& Format(std::string_view format, ...);

    // Caution: view is only valid until tt_string is modified or destroyed!
    tt_string_view subview(size_t start, size_t len) const;

    // Converts all backslashes in the string to forward slashes.
    //
    // Note: Windows works just fine using forward slashes instead of backslashes.
    tt_string& backslashestoforward();

    // Converts all forward slashes in the string to backward slashes.
    //
    // Note: Windows API functions normally work fine with forward slashes instead of
    // backslashes.
    tt_string& forwardslashestoback();

    // Add a trailing forward slash (default is only if there isn't one already)
    void addtrailingslash(bool always = false)
    {
        if (always || back() != '/')
            push_back('/');
    }

    // Returns true if current filename contains the specified case-insensitive extension.
    bool has_extension(std::string_view ext) const { return tt::is_sameas(extension(), ext, tt::CASE::either); }

    // Returns true if current filename contains the specified case-insensitive file name.
    bool has_filename(std::string_view name) const { return tt::is_sameas(filename(), name, tt::CASE::either); }

    // Returns a view to the current extension. View is empty if there is no extension.
    //
    // Caution: view is only valid until tt_string is modified or destroyed.
    tt_string_view extension() const noexcept;

    // Returns a view to the current filename. View is empty if there is no filename.
    //
    // Caution: view is only valid until tt_string is modified or destroyed.
    tt_string_view filename() const noexcept;

    // Returns offset to the current filename or tt::npos if there is no filename.
    size_t find_filename() const noexcept;

    // Replaces any existing extension with a new extension, or appends the extension if the
    // name doesn't currently have an extension.
    //
    // Returns view to the entire string.
    tt_string& replace_extension(std::string_view newExtension);

    // Replaces the extension portion of the string. Returns a view to the entire string.
    tt_string& remove_extension() { return replace_extension(std::string_view {}); };

    // Replaces the filename portion of the string. Returns a view to the entire string.
    tt_string& replace_filename(std::string_view newFilename);
    tt_string& replace_filename(std::wstring_view newFilename) { return replace_filename(tt::utf16to8(newFilename)); }

    // Removes the filename portion of the string. Returns a view to the entire string.
    tt_string& remove_filename() { return replace_filename(""); }

    // Appends the filename -- assumes current string is a path. This will add a trailing
    // slash (if needed) before adding the filename.
    tt_string& append_filename(std::string_view filename);
    tt_string& append_filename(std::wstring_view filename) { return append_filename(tt::utf16to8(filename)); }

    // Makes the current path relative to the supplied path. Use "." to be relative to the current
    // directory. Supplied path should not contain a filename.
    //
    // Unlike fs::relative(), this will not resolve symbolic links, allowing it to work
    // even when you are using a directory with a symbolic link to a different drive.
    tt_string& make_relative(std::string_view relative_to);

    // Changes any current path to an absolute path.
    tt_string& make_absolute();

    // Replaces current string with the full path to the current working directory.
    tt_string& assignCwd();

    // Returns true if the current string refers to an existing file.
    bool file_exists() const;

    // Returns true if the current string refers to an existing directory.
    bool dir_exists() const;

    tt_string& operator<<(std::string_view str)
    {
        *this += str;
        return *this;
    }

    tt_string& operator<<(std::wstring_view str)
    {
        tt::utf16to8(str, *this);
        return *this;
    }

    tt_string& operator<<(char ch)
    {
        *this += ch;
        return *this;
    }

    tt_string& operator<<(int value)
    {
        *this += std::to_string(value);
        return *this;
    }

    tt_string& operator<<(size_t value)
    {
        *this += std::to_string(value);
        return *this;
    }

    tt_string& assign_wx(const wxString& str)
    {
        *this = str.utf8_string();
        return *this;
    }
    tt_string& append_wx(const wxString& str)
    {
        *this += str.utf8_string();
        return *this;
    }

};  // end tt_string class
