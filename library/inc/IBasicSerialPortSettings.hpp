#ifndef _WX_I_SERIAL_PORT_BASIC_SETTINGS_HPP
#define _WX_I_SERIAL_PORT_BASIC_SETTINGS_HPP

#include <cstdint>
#include <string>
#include "DataBits.hpp"

namespace wx
{
    template<typename StringType>
    struct IBasicSerialPortSettings
    {
        virtual ~IBasicSerialPortSettings() = default;
        
        virtual const StringType& GetPortName() const = 0;
        virtual uint32_t GetBaudRate() const = 0;
        virtual DataBits GetDataBits() const = 0;
        
        virtual void SetPortName(const StringType& name) = 0;
        virtual void SetBaudRate(uint32_t rate) = 0;
        virtual void SetDataBits(DataBits dataBits) = 0;
    };
}

#endif // _WX_I_SERIAL_PORT_BASIC_SETTINGS_HPP