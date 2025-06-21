#ifndef _WX_I_SERIAL_PORT_TRANSPORT_HPP
#define _WX_I_SERIAL_PORT_TRANSPORT_HPP

#include "DataBits.hpp"
#include "StopBits.hpp"
#include "Parity.hpp"
#include "FlowControl.hpp"
#include "ISerialPortSettingsProvider.hpp"

namespace wx
{
    template<typename StringType>
    struct ISerialPortTransport
    {
        virtual ~ISerialPortTransport()  = default;

        virtual void Open() = 0;
        virtual void Close() = 0;

        virtual void SetRequestToSend(bool state) = 0;
        
        virtual void ApplySerialPortSettings(const ISerialPortSettingsProvider<StringType>& settings) = 0;

        virtual void ApplySerialPortBaudRate(uint32_t baudRate) = 0;
        virtual void ApplySerialPortStopBits(StopBits stopBits) = 0;
        virtual void ApplySerialPortDataBits(DataBits dataBits) = 0;
        virtual void ApplySerialPortParity(Parity parity) = 0;
        virtual void ApplySerialPortFlowControl(FlowControl flowControl) = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_TRANSPORT_HPP