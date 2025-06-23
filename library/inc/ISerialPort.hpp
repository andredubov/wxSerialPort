#ifndef _WX_I_SERIAL_PORT_HPP
#define _WX_I_SERIAL_PORT_HPP

#include <cstdint>
#include "Parity.hpp"
#include "FlowControl.hpp"
#include "StopBits.hpp"
#include "DataBits.hpp"
#include "ISerialPortSettingsProvider.hpp"

namespace wx
{
    template<typename StringType>
    struct ISerialPort
    {
        virtual ~ISerialPort()  = default;

        virtual void Open(const StringType& portName, 
            uint32_t baudRate, 
            DataBits dataBits, 
            StopBits stopBits, 
            Parity parity, 
            FlowControl flowControl) = 0;

        virtual void Close() = 0;

        virtual void SetRequestToSend(bool state) = 0;

        virtual void SetBaudRate(uint32_t baudRate) = 0;
        virtual void SetStopBits(StopBits stopBits) = 0;
        virtual void SetDataBits(DataBits dataBits) = 0;
        virtual void SetParity(Parity parity) = 0;
        virtual void SetFlowControl(FlowControl flowControl) = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_HPP