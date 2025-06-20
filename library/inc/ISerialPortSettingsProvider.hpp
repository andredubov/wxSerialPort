#ifndef _WX_I_SERIAL_PORT_SETTINGS_PROVIDER_HPP
#define _WX_I_SERIAL_PORT_SETTINGS_PROVIDER_HPP

#include <cstdint>
#include <string>
#include "Parity.hpp"
#include "FlowControl.hpp"
#include "StopBits.hpp"
#include "DataBits.hpp"

namespace wx
{
    template <typename StringType>
    struct ISerialPortSettingsProvider
    {
        virtual ~ISerialPortSettingsProvider() = default;

        virtual StringType GetPortName() const = 0;
        virtual uint32_t GetBaudRate() const = 0;
        virtual DataBits GetDataBits() const = 0;
        virtual StopBits GetStopBits() const = 0;
        virtual Parity GetParity() const = 0;
        virtual FlowControl GetFlowControl() const = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_SETTINGS_PROVIDER_HPP