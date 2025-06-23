#include "SerialPort.hpp"
#include "AsioSerialPortTransport.hpp"
#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif // __WXMSW__

namespace wx
{
    std::vector<wxString> SerialPort::GetPortNames()
    {
        std::vector<wxString> vStrPortNames;

    #ifdef __WXMSW__
        wxRegKey regKey(wxRegKey::HKLM, wxS("HARDWARE\\DEVICEMAP\\SERIALCOMM"));

        if (!regKey.Exists())
        {
            return vStrPortNames;
        }

        wxASSERT(regKey.Exists());

        wxString strValueName;
        long longIndex;

        // Enumerate all values
        bool bCont = regKey.GetFirstValue(strValueName, longIndex);

        while (bCont)
        {
            wxRegKey::ValueType valueType = regKey.GetValueType(strValueName);

            if ((valueType == wxRegKey::Type_String || valueType == wxRegKey::Type_Expand_String || valueType == wxRegKey::Type_Multi_String) && !strValueName.empty())
            {
                wxString strValueData;
                regKey.QueryValue(strValueName, strValueData);
                vStrPortNames.push_back(strValueData);
            }

            bCont = regKey.GetNextValue(strValueName, longIndex);
        }
        
        std::sort(vStrPortNames.begin(), vStrPortNames.end(), [](const wxString& a, const wxString& b) {
            long numA, numB;
            a.AfterFirst(wxT('M')).ToLong(&numA);  // "COM10" → "10" → 10
            b.AfterFirst(wxT('M')).ToLong(&numB);  // "COM2"  → "2"  → 2
            return numA < numB;
        });        
    #else // !__WXMSW__
        wxArrayString arrStrFiles;
        wxDir::GetAllFiles(wxS("/dev/"), &arrStrFiles, wxS("ttyS*"), wxDIR_FILES);

        for (wxArrayString::const_iterator it = arrStrFiles.begin(); it != arrStrFiles.end(); ++it)
            vStrPortNames.push_back(*it);
    #endif // __WXMSW__

        return vStrPortNames;
    }

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