#ifndef _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP
#define _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP

#include <map>
#include <wx/string.h>
#include <boost/asio.hpp>
#include "ISerialPortTransport.hpp"
#include "ISerialPortSettings.hpp"

namespace wx
{
    namespace asio = boost::asio;

    class AsioSerialPortTransport : public ISerialPortTransport<wxString>
    {
        asio::io_context io_context;
        asio::serial_port serial_port;
        asio::serial_port::native_handle_type native_handle;
        std::shared_ptr<ISerialPortSettings<wxString>> serial_port_settings;

        bool IsHandleValid() const;

#ifdef _WIN32
        std::string GetLastErrorString(DWORD errorCode);
#endif

    public:
        explicit AsioSerialPortTransport();
        explicit AsioSerialPortTransport(std::shared_ptr<ISerialPortSettings<wxString>> settings);

        virtual ~AsioSerialPortTransport() = default;

        AsioSerialPortTransport(const AsioSerialPortTransport& other) = delete;
        AsioSerialPortTransport(const AsioSerialPortTransport&& other) = delete;
        AsioSerialPortTransport& operator=(const AsioSerialPortTransport& rhs) = delete;
        AsioSerialPortTransport& operator=(const AsioSerialPortTransport&& rhs) = delete;

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

#endif // _WX_ASIO_SERIAL_PORT_TRANSPORT_HPP
