#ifndef _WX_ASIO_SERIAL_PORT_PARITY_ENUM_CONVERTER_HPP
#define _WX_ASIO_SERIAL_PORT_PARITY_ENUM_CONVERTER_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>
#include <wx/translation.h>
#include <boost/asio.hpp>

namespace wx
{
    namespace asio = boost::asio;
    
    // Template specialization for asio::serial_port_base::parity::type and std::string 
    
    template <>
    inline const std::map<asio::serial_port_base::parity::type, std::string> &
    EnumConverter<asio::serial_port_base::parity::type, std::string>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::parity::type, std::string> map = {
            {asio::serial_port_base::parity::type::none, "None"},
            {asio::serial_port_base::parity::type::odd, "Odd"},
            {asio::serial_port_base::parity::type::even, "Even"}};

        return map;
    }

    template <>
    inline const std::map<std::string, asio::serial_port_base::parity::type> &
    EnumConverter<asio::serial_port_base::parity::type, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, asio::serial_port_base::parity::type> map = {
            {"None", asio::serial_port_base::parity::type::none},
            {"Odd", asio::serial_port_base::parity::type::odd},
            {"Even", asio::serial_port_base::parity::type::even}};

        return map;
    }

    // Template specialization for asio::serial_port_base::parity::type and wxString

    template <>
    inline const std::map<asio::serial_port_base::parity::type, wxString> &
    EnumConverter<asio::serial_port_base::parity::type, wxString>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::parity::type, wxString> map = {
            {asio::serial_port_base::parity::type::none, wxGetTranslation("None")},
            {asio::serial_port_base::parity::type::odd, wxGetTranslation("Odd")},
            {asio::serial_port_base::parity::type::even, wxGetTranslation("Even")}};

        return map;
    }

    template <>
    inline const std::map<wxString, asio::serial_port_base::parity::type> &
    EnumConverter<asio::serial_port_base::parity::type, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, asio::serial_port_base::parity::type> map = {
            {wxGetTranslation("None"), asio::serial_port_base::parity::type::none},
            {wxGetTranslation("Odd"), asio::serial_port_base::parity::type::odd},
            {wxGetTranslation("Even"), asio::serial_port_base::parity::type::even}};

        return map;
    }
}

#endif // _WX_ASIO_SERIAL_PORT_PARITY_ENUM_CONVERTER_HPP