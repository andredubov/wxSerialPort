#include "SerialPort.hpp"
#include "AsioSerialPortTransport.hpp"

namespace wx
{
    SerialPort::SerialPort() : 
        ISerialPort(),
        transport(AsioSerialPortTransport{})
    {

    }

    SerialPort::SerialPort(ISerialPortTransport<wxString>& transport) : 
        ISerialPort(),
        transport(transport)
    {

    }

    void SerialPort::Open()
    {
        transport.Open();
    }

    void SerialPort::Close()
    {
        transport.Close();
    }

    void SerialPort::SetRequestToSend(bool state)
    {
        transport.SetRequestToSend(state);
    }

    void SerialPort::ApplySerialPortSettings(const ISerialPortSettingsProvider<wxString>& settings)
    {
        transport.ApplySerialPortSettings(settings);
    }

    void SerialPort::ApplySerialPortBaudRate(uint32_t baudRate)
    {
        transport.ApplySerialPortBaudRate(baudRate);
    }

    void SerialPort::ApplySerialPortDataBits(DataBits dataBits)
    {
        transport.ApplySerialPortDataBits(dataBits);
    }

    void SerialPort::ApplySerialPortStopBits(StopBits stopBits)
    {
        transport.ApplySerialPortStopBits(stopBits);
    }

    void SerialPort::ApplySerialPortParity(Parity parity)
    {
        transport.ApplySerialPortParity(parity);
    }

    void SerialPort::ApplySerialPortFlowControl(FlowControl flowControl)
    {
        transport.ApplySerialPortFlowControl(flowControl);
    }
}
