#ifndef _WX_SERIAL_PORT_STOP_BITS_HPP
#define _WX_SERIAL_PORT_STOP_BITS_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>

namespace wx
{
    enum class StopBits
    {
        One = 1,
        Two,
        OneAndHalf
    };

    // Template specialization for StopBits and std::string 

    template <>
    inline const std::map<StopBits, std::string> &EnumConverter<StopBits, std::string>::GetToStringMap()
    {
        static const std::map<StopBits, std::string> map = {
            {StopBits::One, "1"},
            {StopBits::OneAndHalf, "1.5"},
            {StopBits::Two, "2"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, StopBits> &EnumConverter<StopBits, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, StopBits> map = {
            {"1", StopBits::One},
            {"1.5", StopBits::OneAndHalf},
            {"2", StopBits::Two}
        };

        return map;
    }

    // Template specialization for StopBits and wxString

    template <>
    inline const std::map<StopBits, wxString> &EnumConverter<StopBits, wxString>::GetToStringMap()
    {
        static const std::map<StopBits, wxString> map = {
            {StopBits::One, wxT("1")},
            {StopBits::OneAndHalf, wxT("1.5")},
            {StopBits::Two, wxT("2")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, StopBits> &EnumConverter<StopBits, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, StopBits> map = {
            {wxT("1"), StopBits::One},
            {wxT("1.5"), StopBits::OneAndHalf},
            {wxT("2"), StopBits::Two}
        };

        return map;
    }
}

#endif // _WX_SERIAL_PORT_STOP_BITS_HPP