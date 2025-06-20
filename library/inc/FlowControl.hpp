#ifndef _WX_SERIAL_PORT_FLOW_CONTROL_HPP
#define _WX_SERIAL_PORT_FLOW_CONTROL_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>
#include <wx/translation.h>

namespace wx
{
    enum class FlowControl
    {
        None,
        Software,
        Hardware
    };

    // Template specialization for FlowControl and std::string 

    template <>
    inline const std::map<FlowControl, std::string> &EnumConverter<FlowControl, std::string>::GetToStringMap()
    {
        static const std::map<FlowControl, std::string> map = {
            {FlowControl::None, "None"},
            {FlowControl::Hardware, "Hardware"},
            {FlowControl::Software, "Xon / Xoff"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, FlowControl> &EnumConverter<FlowControl, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, FlowControl> map = {
            {"None", FlowControl::None},
            {"Hardware", FlowControl::Hardware},
            {"Xon / Xoff", FlowControl::Software}
        };

        return map;
    }

    // Template specialization for FlowControl and wxString

    template <>
    inline const std::map<FlowControl, wxString> &EnumConverter<FlowControl, wxString>::GetToStringMap()
    {
        static const std::map<FlowControl, wxString> map = {
            {FlowControl::None, wxGetTranslation("None")},
            {FlowControl::Hardware, wxGetTranslation("Hardware")},
            {FlowControl::Software, wxGetTranslation("Xon / Xoff")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, FlowControl> &EnumConverter<FlowControl, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, FlowControl> map = {
            {wxGetTranslation("None"), FlowControl::None},
            {wxGetTranslation("Hardware"), FlowControl::Hardware},
            {wxGetTranslation("Xon / Xoff"), FlowControl::Software}
        };

        return map;
    }
}

#endif // _WX_SERIAL_PORT_FLOW_CONTROL_HPP