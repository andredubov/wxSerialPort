#ifndef _WX_I_SERIAL_PORT_SETTINGS_HPP
#define _WX_I_SERIAL_PORT_SETTINGS_HPP

#include <string>
#include "IBasicSerialPortSettings.hpp"
#include "IAdvancedSerialPortSettings.hpp"

namespace wx
{
    template<typename StringType>
    struct ISerialPortSettings : public IBasicSerialPortSettings<StringType>, public IAdvancedSerialPortSettings
    {
        virtual ~ISerialPortSettings() = default;
    };
}

#endif // _WX_I_SERIAL_PORT_BASIC_SETTINGS_HPP