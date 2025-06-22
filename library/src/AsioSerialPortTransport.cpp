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
        serial_port_settings(SerialPortSettings{}),
        io_context(),
        serial_port(io_context),
        native_handle(0)
    {

    }

    AsioSerialPortTransport::AsioSerialPortTransport(const ISerialPortSettingsProvider<wxString>& settings) : 
        ISerialPortTransport(),
        serial_port_settings(settings),
        io_context(),
        serial_port(io_context),
        native_handle(0)
    {

    }

    void AsioSerialPortTransport::Open()
    {
        try
        {
            serial_port.open(serial_port_settings.GetPortName().ToStdString());
        }
        catch (const boost::system::system_error &e)
        {
            auto message = wxString::Format("Error opening %s: %s", 
                serial_port_settings.GetPortName().ToStdString().c_str(), 
                e.what()
            );
            throw std::runtime_error(message);
        }

        if (!serial_port.is_open())
        {
            throw std::runtime_error("Failed to open port");
        }

        ApplySerialPortBaudRate(serial_port_settings.GetBaudRate());
        ApplySerialPortStopBits(serial_port_settings.GetStopBits());
        ApplySerialPortDataBits(serial_port_settings.GetDataBits());
        ApplySerialPortParity(serial_port_settings.GetParity());
        ApplySerialPortFlowControl(serial_port_settings.GetFlowControl());

        native_handle = serial_port.native_handle();

        if (auto ok = IsHandleValid(); !ok)
        {
            auto message = wxT("Invalid native handle: port ") + serial_port_settings.GetPortName() + wxT(" is not open");
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

    void AsioSerialPortTransport::ApplySerialPortSettings(const ISerialPortSettingsProvider<wxString>& settings)
    {
        ApplySerialPortBaudRate(settings.GetBaudRate());
        ApplySerialPortDataBits(settings.GetDataBits());
        ApplySerialPortStopBits(settings.GetStopBits());
        ApplySerialPortParity(settings.GetParity());
        ApplySerialPortFlowControl(settings.GetFlowControl());
    }

    void AsioSerialPortTransport::ApplySerialPortBaudRate(uint32_t baud_rate)
    {
        serial_port.set_option(asio::serial_port_base::baud_rate(baud_rate));
        asio::serial_port_base::baud_rate current_baud_rate;
        serial_port.get_option(current_baud_rate);

        if (current_baud_rate.value() != baud_rate)
        {
            auto message = wxString::Format("Failed to set baud rate. Requested:  {} actual: {}", 
                baud_rate, 
                current_baud_rate.value()
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::ApplySerialPortDataBits(DataBits data_bits)
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

        auto data_bits_n = static_cast<int>(data_bits);
        auto current_data_bits_n = static_cast<int>(current_data_bits.value());

        if (current_data_bits_n != data_bits_n)
        {
            auto message = wxString::Format("Failed to set data bits. Requested: {}, actual: {}",
                data_bits_n,
                current_data_bits_n
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::ApplySerialPortStopBits(StopBits stop_bits)
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
            auto message = wxString::Format("Failed to set stop bits. Requested: {}, actual: {}",
                stop_bits_str,
                current_stop_bits_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::ApplySerialPortParity(Parity parity)
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
            auto message = wxString::Format("Failed to set stop bits. Requested: {} , actual:  {}",
                parity_str,
                current_parity_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }

    void AsioSerialPortTransport::ApplySerialPortFlowControl(FlowControl flow_control)
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
            auto message = wxString::Format("Failed to set stop bits. Requested: {} , actual: {}", 
                flow_control_str, 
                current_flow_control_str
            ).ToStdString();

            throw std::runtime_error(message);
        }
    }
}