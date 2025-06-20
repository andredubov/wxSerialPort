#ifndef _WX_I_SERIAL_PORT_TRANSPORT_HPP
#define _WX_I_SERIAL_PORT_TRANSPORT_HPP

#include <memory>
#include "ISerialPortSettings.hpp"

namespace wx
{
    template<typename StringType>
    struct ISerialPortTransport
    {
        virtual ~ISerialPortTransport()  = default;

        virtual void Open() = 0;
        virtual void Close() = 0;

        virtual void SetRequestToSend(bool state) = 0;
        
        virtual void ApplySerialPortSettings(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
        virtual void ApplySerialPortBaudRate(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
        virtual void ApplySerialPortStopBits(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
        virtual void ApplySerialPortDataBits(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
        virtual void ApplySerialPortParity(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
        virtual void ApplySerialPortFlowControl(std::shared_ptr<ISerialPortSettings<StringType>> settings) = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_TRANSPORT_HPP