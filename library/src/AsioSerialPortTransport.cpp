#include "AsioSerialPortTransport.hpp"
#include "EnumConverter.hpp"
#include "AsioStopBitsEnumConverter.hpp"
#include "AsioParityEnumConverter.hpp"
#include "AsioFlowControlEnumConverter.hpp"
#include "SerialPortSettings.hpp"

namespace wx
{
    AsioSerialPortTransport::AsioSerialPortTransport() : 
        ISerialPortTransport(),
        io_context(),
        serial_port(io_context),
        native_handle(0)
    {

    }

    void AsioSerialPortTransport::Open(const wxString& portName, uint32_t baudRate, DataBits dataBits, StopBits stopBits, Parity parity, FlowControl flowControl)
    {
        try
        {
            serial_port.open(portName.ToStdString());
        }
        catch (const boost::system::system_error &e)
        {
            auto message = wxString::Format("Error opening {}: {}", 
                portName.ToStdString(), 
                e.what()
            );
            throw std::runtime_error(message);
        }

        if (!serial_port.is_open())
        {
            throw std::runtime_error("Failed to open port");
        }

        SetBaudRate(baudRate);
        SetDataBits(dataBits);
        SetStopBits(stopBits);        
        SetParity(parity);
        SetFlowControl(flowControl);

        native_handle = serial_port.native_handle();

        if (auto ok = IsHandleValid(); !ok)
        {
            auto message = wxT("Invalid native handle: port ") + portName + wxT(" is not open");
            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::Close()
    {
        if (serial_port.is_open())
        {
            serial_port.close();
        }
    }

    void AsioSerialPortTransport::SetRequestToSend(bool state)
    {
    #ifdef _WIN32
        HANDLE handle = reinterpret_cast<HANDLE>(native_handle);
        DWORD cmd = state ? SETRTS : CLRRTS;

        if (!::EscapeCommFunction(handle, cmd))
        {
            auto errorCode = ::GetLastError();
            auto errorMessage = GetLastErrorString(errorCode);
            auto message = wxString::Format("SetRTS failed, error code: 0x%x - %s", 
                errorCode, 
                errorMessage
            ).ToStdString();

            throw std::runtime_error(message);
        }
    #else
        int status = 0;

        if (::ioctl(native_handle, TIOCMGET, &status) == -1)
        {
            int errorCode = errno;
            auto message = wxString::Format("Failed to get RTS state: {} [errno: {}]", 
                strerror(errorCode), 
                errorCode
            ).ToStdString();

            throw std::runtime_error(message);
        }

        if (state)
        {
            status |= TIOCM_RTS;
        }
        else
        {
            status &= ~TIOCM_RTS;
        }

        if (::ioctl(native_handle, TIOCMSET, &status) == -1)
        {
            int errorCode = errno;
            auto message = wxString::Format("Failed to set RTS state: {} [errno: {}]", 
                strerror(errorCode), 
                errorCode
            ).ToStdString();

            throw std::runtime_error(message);
        }
    #endif
    }

    void AsioSerialPortTransport::SetBaudRate(uint32_t baud_rate)
    {
        serial_port.set_option(asio::serial_port_base::baud_rate(baud_rate));
        asio::serial_port_base::baud_rate current_baud_rate;
        serial_port.get_option(current_baud_rate);

        if (current_baud_rate.value() != baud_rate)
        {
            auto message = wxString::Format("Failed to set baud rate. Requested: %u actual: %u", 
                baud_rate, 
                current_baud_rate.value()
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::SetDataBits(DataBits data_bits)
    {
        switch (data_bits)
        {
        case DataBits::Five:
            serial_port.set_option(asio::serial_port_base::character_size(5));
            break;
        case DataBits::Six:
            serial_port.set_option(asio::serial_port_base::character_size(6));
            break;
        case DataBits::Seven:
            serial_port.set_option(asio::serial_port_base::character_size(7));
            break;
        case DataBits::Eight:
            serial_port.set_option(asio::serial_port_base::character_size(8));
            break;
        }

        asio::serial_port_base::character_size current_data_bits;
        serial_port.get_option(current_data_bits);

        auto data_bits_n = static_cast<uint32_t>(data_bits);
        auto current_data_bits_n = static_cast<uint32_t>(current_data_bits.value());

        if (current_data_bits_n != data_bits_n)
        {
            auto message = wxString::Format("Failed to set data bits. Requested: %u, actual: %u",
                data_bits_n,
                current_data_bits_n
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::SetStopBits(StopBits stop_bits)
    {
        switch (stop_bits)
        {
        case StopBits::One:
            serial_port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
            break;
        case StopBits::OneAndHalf:
            serial_port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::onepointfive));
            break;
        case StopBits::Two:
            serial_port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::two));
            break;
        }

        asio::serial_port_base::stop_bits current_stop_bits;
        serial_port.get_option(current_stop_bits);

        auto stop_bits_str = EnumConverter<StopBits, wxString>::ToString(stop_bits);
        auto current_stop_bits_str = EnumConverter<asio::serial_port_base::stop_bits::type, wxString>::ToString(current_stop_bits.value());

        if (stop_bits_str != current_stop_bits_str)
        {
            auto message = wxString::Format("Failed to set stop bits. Requested: %s, actual: %s",
                stop_bits_str,
                current_stop_bits_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::SetParity(Parity parity)
    {
        switch (parity)
        {
        case Parity::None:
            serial_port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
            break;
        case Parity::Odd:
            serial_port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::odd));
            break;
        case Parity::Even:
            serial_port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
            break;
        }

        asio::serial_port_base::parity current_parity;
        serial_port.get_option(current_parity);

        auto parity_str = EnumConverter<Parity, wxString>::ToString(parity);
        auto current_parity_str = EnumConverter<asio::serial_port_base::parity::type, wxString>::ToString(current_parity.value());

        if (parity_str != current_parity_str)
        {
            auto message = wxString::Format("Failed to set stop bits. Requested: %s, actual: %s",
                parity_str,
                current_parity_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::SetFlowControl(FlowControl flow_control)
    {
        switch (flow_control)
        {
        case FlowControl::None:
            serial_port.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
            break;
        case FlowControl::Software:
            serial_port.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::software));
            break;
        case FlowControl::Hardware:
            serial_port.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::hardware));
            break;
        }

        asio::serial_port_base::flow_control current_flow_control;
        serial_port.get_option(current_flow_control);

        auto flow_control_str = EnumConverter<FlowControl, wxString>::ToString(flow_control);
        auto current_flow_control_str = EnumConverter<asio::serial_port_base::flow_control::type, wxString>::ToString(current_flow_control.value());

        if (flow_control_str != current_flow_control_str)
        {
            auto message = wxString::Format("Failed to set stop bits. Requested: %s, actual: %s", 
                flow_control_str, 
                current_flow_control_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    bool AsioSerialPortTransport::IsHandleValid() const
    {
    #ifdef _WIN32
        return native_handle && reinterpret_cast<HANDLE>(native_handle) != INVALID_HANDLE_VALUE;
    #else
        return native_handle >= 0;
    #endif
    }

    #ifdef _WIN32
    std::string AsioSerialPortTransport::GetLastErrorString(DWORD errorCode)
    {
        LPTSTR tbuffer = nullptr;

        DWORD size = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPTSTR>(&tbuffer),
            0,
            nullptr);

        if (0 == size)
        {
            return "Failed to get error message";
        }

    #ifdef UNICODE
        // для Unicode проектов
        std::wstring wmessage(tbuffer, size);
        ::LocalFree(tbuffer);

        int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wmessage.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string message(utf8Size, '\0');
        WideCharToMultiByte(CP_UTF8, 0, wmessage.c_str(), -1, &message[0], utf8Size, nullptr, nullptr);
    #else
        // для ANSI проектов
        std::string message(tbuffer, size);
        ::LocalFree(tbuffer);
    #endif

        // удаляем \r\n
        message.erase(std::remove(message.begin(), message.end(), '\r'), message.end());
        message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
        
        // return wxString(message.c_str(), wxConvLocal);
        return message;
    }
    #endif
}