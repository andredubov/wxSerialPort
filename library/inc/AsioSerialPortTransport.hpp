#ifndef _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP
#define _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP

#include <map>
#include <wx/string.h>
#include <boost/asio.hpp>
#include "ISerialPortTransport.hpp"

namespace wx
{
    namespace asio = boost::asio;

    class AsioSerialPortTransport : public ISerialPortTransport<wxString>
    {
        asio::io_context io_context;
        asio::serial_port serial_port;
        asio::serial_port::native_handle_type native_handle;

        bool IsHandleValid() const;

#ifdef _WIN32
        std::string GetLastErrorString(DWORD errorCode);
#endif

    public:
        explicit AsioSerialPortTransport();

        virtual ~AsioSerialPortTransport() = default;

        AsioSerialPortTransport(const AsioSerialPortTransport& other) = delete;
        AsioSerialPortTransport(const AsioSerialPortTransport&& other) = delete;
        AsioSerialPortTransport& operator=(const AsioSerialPortTransport& rhs) = delete;
        AsioSerialPortTransport& operator=(const AsioSerialPortTransport&& rhs) = delete;

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

#endif // _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP
