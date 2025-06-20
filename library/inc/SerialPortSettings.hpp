#ifndef _WX_SERIAL_PORT_SETTINGS_HPP
#define _WX_SERIAL_PORT_SETTINGS_HPP

#include <wx/string.h>
#include "ISerialPortSettings.hpp"

namespace wx
{
    class SerialPortSettings : public ISerialPortSettings<wxString>
    {
        wxString portName;
        uint32_t baudRate;
        DataBits dataBits;
        StopBits stopBits;
        Parity parity;
        FlowControl flowControl;

    public:
        explicit SerialPortSettings(
            wxString portName = wxT(""),
            uint32_t baudRate = 9600u,
            DataBits dataBits = DataBits::Eight,
            StopBits stopBits = StopBits::One,
            Parity parity = Parity::None,
            FlowControl flowControl = FlowControl::None
        );

        virtual const wxString& GetPortName() const override;
        virtual uint32_t GetBaudRate() const override;
        virtual DataBits GetDataBits() const override;
        virtual StopBits GetStopBits() const override;
        virtual Parity GetParity() const override;
        virtual FlowControl GetFlowControl() const override;

        void SetPortName(const wxString& portName);
        void SetBaudRate(uint32_t baudRate);
        void SetDataBits(DataBits dataBits);
        void SetStopBits(StopBits stopBits);
        void SetParity(Parity parity);
        void SetFlowControl(FlowControl flowControl);
    };
}

#endif // _WX_SERIAL_PORT_SETTINGS_HPP