#ifndef _WX_SERIAL_PORT_HPP
#define _WX_SERIAL_PORT_HPP

#include <wx/string.h>
#include "ISerialPort.hpp"
#include "ISerialPortTransport.hpp"

namespace wx
{
    class SerialPort : public ISerialPort<wxString>
    {
        ISerialPortTransport<wxString>& transport;

    public:
        explicit SerialPort();
        explicit SerialPort(ISerialPortTransport<wxString>& transport);

        virtual ~SerialPort() = default;

        SerialPort(const SerialPort& other) = delete;
        SerialPort(const SerialPort&& other) = delete;
        SerialPort& operator=(const SerialPort& rhs) = delete;
        SerialPort& operator=(const SerialPort&& rhs) = delete;

        void Open() override;
        void Close() override;

        void SetRequestToSend(bool state) override;

        void ApplySerialPortSettings(const ISerialPortSettingsProvider<wxString>& settings) override;

        void ApplySerialPortBaudRate(uint32_t baudRate) override;
        void ApplySerialPortStopBits(StopBits stopBits) override;
        void ApplySerialPortDataBits(DataBits dataBits) override;
        void ApplySerialPortParity(Parity parity) override;
        void ApplySerialPortFlowControl(FlowControl flowControl) override;
    };
}

#endif // _WX_SERIAL_PORT_HPP