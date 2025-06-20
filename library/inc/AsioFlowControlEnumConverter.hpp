#ifndef _WX_ASIO_SERIAL_PORT_FLOW_CONTROL_ENUM_CONVERTER_HPP
#define _WX_ASIO_SERIAL_PORT_FLOW_CONTROL_ENUM_CONVERTER_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>
#include <boost/asio.hpp>

namespace wx
{
    namespace asio = boost::asio;

    // Template specialization for asio::serial_port_base::flow_control::type and std::string 
    
    template <>
    inline const std::map<asio::serial_port_base::flow_control::type, std::string> &
    EnumConverter<asio::serial_port_base::flow_control::type, std::string>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::flow_control::type, std::string> map = {
            {asio::serial_port_base::flow_control::type::none, "None"},
            {asio::serial_port_base::flow_control::type::hardware, "Hardware"},
            {asio::serial_port_base::flow_control::type::software, "Software"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, asio::serial_port_base::flow_control::type> &
    EnumConverter<asio::serial_port_base::flow_control::type, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, asio::serial_port_base::flow_control::type> map = {
            {"None", asio::serial_port_base::flow_control::type::none},
            {"Hardware", asio::serial_port_base::flow_control::type::hardware},
            {"Software", asio::serial_port_base::flow_control::type::software}
        };

        return map;
    }

    // Template specialization for asio::serial_port_base::flow_control::type and wxString

    template <>
    inline const std::map<asio::serial_port_base::flow_control::type, wxString> &
    EnumConverter<asio::serial_port_base::flow_control::type, wxString>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::flow_control::type, wxString> map = {
            {asio::serial_port_base::flow_control::type::none, wxT("None")},
            {asio::serial_port_base::flow_control::type::hardware, wxT("Hardware")},
            {asio::serial_port_base::flow_control::type::software, wxT("Software")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, asio::serial_port_base::flow_control::type> &
    EnumConverter<asio::serial_port_base::flow_control::type, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, asio::serial_port_base::flow_control::type> map = {
            {wxT("None"), asio::serial_port_base::flow_control::type::none},
            {wxT("Hardware"), asio::serial_port_base::flow_control::type::hardware},
            {wxT("Software"), asio::serial_port_base::flow_control::type::software}
        };

        return map;
    }
}

#endif // _WX_ASIO_SERIAL_PORT_FLOW_CONTROL_ENUM_CONVERTER_HPP