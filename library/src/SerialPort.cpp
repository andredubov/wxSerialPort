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

    void SerialPort::SetBaudRate(uint32_t baudRate)
    {
        transport.SetBaudRate(baudRate);
    }

    void SerialPort::SetDataBits(DataBits dataBits)
    {
        transport.SetDataBits(dataBits);
    }

    void SerialPort::SetStopBits(StopBits stopBits)
    {
        transport.SetStopBits(stopBits);
    }

    void SerialPort::SetParity(Parity parity)
    {
        transport.SetParity(parity);
    }

    void SerialPort::SetFlowControl(FlowControl flowControl)
    {
        transport.SetFlowControl(flowControl);
    }
}