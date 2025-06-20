#ifndef _WX_I_SERIAL_PORT_ADVANCED_SETTINGS_HPP
#define _WX_I_SERIAL_PORT_ADVANCED_SETTINGS_HPP

#include "StopBits.hpp"
#include "FlowControl.hpp"
#include "Parity.hpp"

namespace wx
{
    struct IAdvancedSerialPortSettings
    {
        virtual ~IAdvancedSerialPortSettings() = default;
        
        virtual StopBits GetStopBits() const = 0;
        virtual FlowControl GetFlowControl() const = 0;
        virtual Parity GetParity() const = 0;
        
        virtual void SetStopBits(StopBits stopBits) = 0;
        virtual void SetFlowControl(FlowControl flowControl) = 0;
        virtual void SetParity(Parity parity) = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_ADVANCED_SETTINGS_HPP