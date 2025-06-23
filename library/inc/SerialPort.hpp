#ifndef _WX_SERIAL_PORT_HPP
#define _WX_SERIAL_PORT_HPP

#include <memory>
#include <wx/string.h>
#include "ISerialPort.hpp"
#include "ISerialPortTransport.hpp"

namespace wx
{
    class SerialPort : public ISerialPort<wxString>
    {
        std::shared_ptr<ISerialPortTransport<wxString>> transport;

    public:
        explicit SerialPort();
        explicit SerialPort(std::shared_ptr<ISerialPortTransport<wxString>> transport);

        virtual ~SerialPort() = default;

        SerialPort(const SerialPort& other) = delete;
        SerialPort(const SerialPort&& other) = delete;
        SerialPort& operator=(const SerialPort& rhs) = delete;
        SerialPort& operator=(const SerialPort&& rhs) = delete;

        void Open(const wxString& portName, 
            uint32_t baudRate = 9600u, 
            DataBits dataBits = DataBits::Eight, 
            StopBits stopBits = StopBits::One, 
            Parity parity = Parity::None, 
            FlowControl flowControl = FlowControl::None) override;

        void Close() override;

        void SetRequestToSend(bool state) override;

        void SetBaudRate(uint32_t baudRate) override;
        void SetStopBits(StopBits stopBits) override;
        void SetDataBits(DataBits dataBits) override;
        void SetParity(Parity parity) override;
        void SetFlowControl(FlowControl flowControl) override;
    };
}

#endif // _WX_SERIAL_PORT_HPP