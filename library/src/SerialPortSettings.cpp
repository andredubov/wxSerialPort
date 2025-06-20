#include "SerialPortSettings.hpp"

namespace wx
{
    SerialPortSettings::SerialPortSettings(
        wxString portName,
        uint32_t baudRate,
        DataBits dataBits,
        StopBits stopBits,
        Parity parity,
        FlowControl flowControl
    ) : 
        ISerialPortSettings(),
        portName(portName),
        baudRate(baudRate),
        dataBits(dataBits),
        stopBits(stopBits),
        parity(parity),
        flowControl(flowControl)
    {
        
    }
    
    const wxString& SerialPortSettings::GetPortName() const
    {
        return portName;
    }

    uint32_t SerialPortSettings::GetBaudRate() const
    {
        return baudRate;
    }

    DataBits SerialPortSettings::GetDataBits() const
    {
        return dataBits;
    }

    StopBits SerialPortSettings::GetStopBits() const
    {
        return stopBits;
    }

    Parity SerialPortSettings::GetParity() const
    {
        return parity;
    }

    FlowControl SerialPortSettings::GetFlowControl() const
    {
        return flowControl;
    }

    void SerialPortSettings::SetPortName(const wxString& newPortName)
    {
        portName = newPortName;
    }

    void SerialPortSettings::SetBaudRate(uint32_t newBaudRate)
    {
        baudRate = newBaudRate;
    }

    void SerialPortSettings::SetDataBits(DataBits newDataBits)
    {
        dataBits = newDataBits;
    }

    void SerialPortSettings::SetStopBits(StopBits newStopBits)
    {
        stopBits = newStopBits;
    }

    void SerialPortSettings::SetParity(Parity newParity)
    {
        parity = newParity;
    }

    void SerialPortSettings::SetFlowControl(FlowControl newFlowControl)
    {
        flowControl = newFlowControl;
    }
}