#ifndef _WX_ASIO_SERIAL_PORT_STOP_BITS_ENUM_CONVERTER_HPP
#define _WX_ASIO_SERIAL_PORT_STOP_BITS_ENUM_CONVERTER_HPP

#include "EnumConverter.hpp"
#include <wx/string.h>
#include <boost/asio.hpp>

namespace wx
{
    namespace asio = boost::asio;

    // Template specialization for asio::serial_port_base::stop_bits::type and std::string 

    template <>
    inline const std::map<asio::serial_port_base::stop_bits::type, std::string>&
    EnumConverter<asio::serial_port_base::stop_bits::type, std::string>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::stop_bits::type, std::string> map = {
            {asio::serial_port_base::stop_bits::type::one, "1"},
            {asio::serial_port_base::stop_bits::type::onepointfive, "1.5"},
            {asio::serial_port_base::stop_bits::type::two, "2"}
        };

        return map;
    }

    template <>
    inline const std::map<std::string, asio::serial_port_base::stop_bits::type>&
    EnumConverter<asio::serial_port_base::stop_bits::type, std::string>::GetFromStringMap()
    {
        static const std::map<std::string, asio::serial_port_base::stop_bits::type> map = {
            {"1", asio::serial_port_base::stop_bits::type::one},
            {"1.5", asio::serial_port_base::stop_bits::type::onepointfive},
            {"2", asio::serial_port_base::stop_bits::type::two}
        };

        return map;
    }

    // Template specialization for asio::serial_port_base::stop_bits::type and wxString

    template <>
    inline const std::map<asio::serial_port_base::stop_bits::type, wxString>&
    EnumConverter<asio::serial_port_base::stop_bits::type, wxString>::GetToStringMap()
    {
        static const std::map<asio::serial_port_base::stop_bits::type, wxString> map = {
            {asio::serial_port_base::stop_bits::type::one, wxT("1")},
            {asio::serial_port_base::stop_bits::type::onepointfive, wxT("1.5")},
            {asio::serial_port_base::stop_bits::type::two, wxT("2")}
        };

        return map;
    }

    template <>
    inline const std::map<wxString, asio::serial_port_base::stop_bits::type> &
    EnumConverter<asio::serial_port_base::stop_bits::type, wxString>::GetFromStringMap()
    {
        static const std::map<wxString, asio::serial_port_base::stop_bits::type> map = {
            {wxT("1"), asio::serial_port_base::stop_bits::type::one},
            {wxT("1.5"), asio::serial_port_base::stop_bits::type::onepointfive},
            {wxT("2"), asio::serial_port_base::stop_bits::type::two}
        };

        return map;
    }
}

#endif // _WX_ASIO_SERIAL_PORT_STOP_BITS_ENUM_CONVERTER_HPP