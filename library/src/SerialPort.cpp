#include "SerialPort.hpp"
#include "AsioSerialPortTransport.hpp"

namespace wx
{
    SerialPort::SerialPort() : 
        ISerialPort(),
        transport()
    {
        transport = std::make_shared<AsioSerialPortTransport>();
    }

    SerialPort::SerialPort(std::shared_ptr<ISerialPortTransport<wxString>> transport) : 
        ISerialPort(),
        transport(transport)
    {

    }

    void SerialPort::Open()
    {
        transport->Open();
    }

    void SerialPort::Close()
    {
        transport->Close();
    }

    void SerialPort::SetRequestToSend(bool state)
    {
        transport->SetRequestToSend(state);
    }

    void SerialPort::ApplySerialPortSettings(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortSettings(settings);
    }

    void SerialPort::ApplySerialPortBaudRate(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortBaudRate(settings);
    }

    void SerialPort::ApplySerialPortDataBits(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortStopBits(settings);
    }

    void SerialPort::ApplySerialPortStopBits(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortStopBits(settings);
    }

    void SerialPort::ApplySerialPortParity(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortStopBits(settings);
    }

    void SerialPort::ApplySerialPortFlowControl(std::shared_ptr<ISerialPortSettings<wxString>> settings)
    {
        transport->ApplySerialPortStopBits(settings);
    }
}
