#include "SerialPort.hpp"
#include "AsioSerialPortTransport.hpp"

namespace wx
{
    SerialPort::SerialPort() : 
        ISerialPort(),
        transport(std::make_unique<AsioSerialPortTransport>())
    {

    }

    SerialPort::SerialPort(std::shared_ptr<ISerialPortTransport<wxString>> transport) : 
        ISerialPort(),
        transport(transport)
    {

    }

    void SerialPort::Open(const wxString& portName, uint32_t baudRate, DataBits dataBits, StopBits stopBits, Parity parity, FlowControl flowControl)
    {
        transport->Open(portName, baudRate, dataBits, stopBits, parity, flowControl);
    }

    void SerialPort::Close()
    {
        transport->Close();
    }

    void SerialPort::SetRequestToSend(bool state)
    {
        transport->SetRequestToSend(state);
    }

    void SerialPort::SetBaudRate(uint32_t baudRate)
    {
        transport->SetBaudRate(baudRate);
    }

    void SerialPort::SetDataBits(DataBits dataBits)
    {
        transport->SetDataBits(dataBits);
    }

    void SerialPort::SetStopBits(StopBits stopBits)
    {
        transport->SetStopBits(stopBits);
    }

    void SerialPort::SetParity(Parity parity)
    {
        transport->SetParity(parity);
    }

    void SerialPort::SetFlowControl(FlowControl flowControl)
    {
        transport->SetFlowControl(flowControl);
    }
}