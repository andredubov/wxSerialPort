#ifndef _WX_SERIAL_PORT_PARITY_HPP
#define _WX_SERIAL_PORT_PARITY_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>
#include <wx/translation.h>

namespace wx
{
    enum class Parity
    {
        None,
        Odd,
        Even
    };

    // Template specialization for Parity and std::string 

    template <>
    inline const std::map<Parity, std::string> &EnumConverter<Parity, std::string>::GetToStringMap()
    {
        static const std::map<Parity, std::string> map = {
            {Parity::None, "None"},
            {Parity::Odd, "Odd"},
            {Parity::Even, "Even"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, Parity> &EnumConverter<Parity, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, Parity> map = {
            {"None", Parity::None},
            {"Odd", Parity::Odd},
            {"Even", Parity::Even}
        };

        return map;
    }

    // Template specialization for Parity and wxString

    template <>
    inline const std::map<Parity, wxString> &EnumConverter<Parity, wxString>::GetToStringMap()
    {
        static const std::map<Parity, wxString> map = {
            {Parity::None, wxGetTranslation("None")},
            {Parity::Odd, wxGetTranslation("Odd")},
            {Parity::Even, wxGetTranslation("Even")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, Parity> &EnumConverter<Parity, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, Parity> map = {
            {wxGetTranslation("None"), Parity::None},
            {wxGetTranslation("Odd"), Parity::Odd},
            {wxGetTranslation("Even"), Parity::Even}
        };

        return map;
    }
}

#endif // _WX_SERIAL_PORT_PARITY_HPP