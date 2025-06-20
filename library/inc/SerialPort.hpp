#ifndef _WX_SERIAL_PORT_HPP
#define _WX_SERIAL_PORT_HPP

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

        void Open() override;
        void Close() override;

        void SetRequestToSend(bool state) override;

        void ApplySerialPortSettings(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
        void ApplySerialPortBaudRate(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
        void ApplySerialPortStopBits(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
        void ApplySerialPortDataBits(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
        void ApplySerialPortParity(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
        void ApplySerialPortFlowControl(std::shared_ptr<ISerialPortSettings<wxString>> settings) override;
    };
}

#endif // _WX_SERIAL_PORT_HPP