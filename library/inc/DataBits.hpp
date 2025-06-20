#ifndef _WX_SERIAL_PORT_DATA_BITS_HPP
#define _WX_SERIAL_PORT_DATA_BITS_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>

namespace wx
{
    enum class DataBits
    {
        Five = 5,
        Six,
        Seven,
        Eight
    };

    // Template specialization for DataBits and std::string 

    template <>
    inline const std::map<DataBits, std::string> &EnumConverter<DataBits, std::string>::GetToStringMap()
    {
        static const std::map<DataBits, std::string> map = {
            {DataBits::Five, "5"},
            {DataBits::Six, "6"},
            {DataBits::Seven, "7"},
            {DataBits::Eight, "8"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, DataBits> &EnumConverter<DataBits, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, DataBits> map = {
            {"5", DataBits::Five},
            {"6", DataBits::Six},
            {"7", DataBits::Seven},
            {"8", DataBits::Eight}
        };

        return map;
    }

    // Template specialization for DataBits and wxString

    template <>
    inline const std::map<DataBits, wxString> &EnumConverter<DataBits, wxString>::GetToStringMap()
    {
        static const std::map<DataBits, wxString> map = {
            {DataBits::Five, wxT("5")},
            {DataBits::Six, wxT("6")},
            {DataBits::Seven, wxT("7")},
            {DataBits::Eight, wxT("8")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, DataBits> &EnumConverter<DataBits, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, DataBits> map = {
            {wxT("5"), DataBits::Five},
            {wxT("6"), DataBits::Six},
            {wxT("7"), DataBits::Seven},
            {wxT("8"), DataBits::Eight}
        };

        return map;
    }
}

#endif // _WX_SERIAL_PORT_DATA_BITS_HPP