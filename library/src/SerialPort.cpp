////////////////////////////////////////////////////////////////////////////////
// Name:      serialport.cpp
// Purpose:   Code for wxSerialPort Class
// Author:    Youcef Kouchkar
// Created:   2018-01-08
// Copyright: (c) 2019 Youcef Kouchkar
// License:   MIT License
////////////////////////////////////////////////////////////////////////////////

#include "SerialPort.hpp"
#include <functional>

#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif

std::vector<wxString> wxSerialPortBase::GetPortNames()
{
    std::vector<wxString> ports;

#ifdef __WXMSW__
    wxRegKey regKey(wxRegKey::HKLM, wxS("HARDWARE\\DEVICEMAP\\SERIALCOMM"));
    if (!regKey.Exists())
        return ports;

    wxString valueName;
    long index;
    bool cont = regKey.GetFirstValue(valueName, index);

    while (cont)
    {
        if (regKey.GetValueType(valueName) == wxRegKey::Type_String && !valueName.empty())
        {
            wxString valueData;
            regKey.QueryValue(valueName, valueData);
            ports.push_back(valueData);
        }
        cont = regKey.GetNextValue(valueName, index);
    }
#else
    wxArrayString files;
    wxDir::GetAllFiles(wxS("/dev/"), &files, wxS("ttyS*"), wxDIR_FILES);
    for (const auto &file : files)
    {
        ports.push_back(file);
    }
#endif

    return ports;
}

wxSerialPort::wxSerialPort()
    : m_serialPort(m_io_context),
      m_timer(m_io_context)
{
    Init();
}

wxSerialPort::wxSerialPort(const std::string &device)
    : m_serialPort(m_io_context, device),
      m_timer(m_io_context),
      m_strPortName(device)
{
    Init();
}

wxSerialPort::wxSerialPort(const wxString &device) : wxSerialPort(device.ToStdString())
{
}

wxSerialPort::wxSerialPort(const char *device) : wxSerialPort(std::string(device))
{
}

wxSerialPort::wxSerialPort(const boost::asio::serial_port::native_handle_type &native_serial_port)
    : m_serialPort(m_io_context, native_serial_port),
      m_timer(m_io_context)
{
    Init();
}

wxSerialPort::wxSerialPort(const wxSerialPort &other)
    : m_serialPort(m_io_context),
      m_timer(m_io_context),
      m_strPortName(other.m_strPortName)
{
    Init();
}

wxSerialPort &wxSerialPort::operator=(const wxSerialPort &other)
{
    if (this != &other)
    {
        m_strPortName = other.m_strPortName;
    }
    return *this;
}

#ifdef BOOST_ASIO_HAS_MOVE
wxSerialPort::wxSerialPort(wxSerialPort &&other) noexcept
    : m_serialPort(std::move(other.m_serialPort)),
      m_timer(std::move(other.m_timer)),
      m_strPortName(std::move(other.m_strPortName)),
      m_last_error(std::move(other.m_last_error)) {}

wxSerialPort &wxSerialPort::operator=(wxSerialPort &&other) noexcept
{
    if (this != &other)
    {
        m_serialPort = std::move(other.m_serialPort);
        m_timer = std::move(other.m_timer);
        m_strPortName = std::move(other.m_strPortName);
        m_last_error = std::move(other.m_last_error);
    }

    return *this;
}
#endif

wxSerialPort::~wxSerialPort()
{
    m_serialPort.close();
}

// Implementation of synchronous operations
std::size_t wxSerialPort::DoReadSome(const boost::asio::mutable_buffer &buffer)
{
    boost::system::error_code error;
    std::size_t ret = m_serialPort.read_some(buffer, error);
    DoSetLastError(error);

    return ret;
}

std::size_t wxSerialPort::DoReadSome(const boost::asio::mutable_buffer &buffer, int timeout)
{
    std::size_t bytes_read = 0;
    m_io_context.restart();
    DoAsyncWaitThenCancelAsyncIO(timeout);

    m_serialPort.async_read_some(
        buffer,
        [&](const boost::system::error_code &error, std::size_t bytes)
        {
            if (!error)
            {
                m_timer.cancel();
            }
            bytes_read = bytes;
            DoSetLastError(error);
        });

    m_io_context.run();

    return bytes_read;
}

std::size_t wxSerialPort::DoWriteSome(const boost::asio::const_buffer &buffer)
{
    boost::system::error_code error;
    std::size_t ret = m_serialPort.write_some(buffer, error);
    DoSetLastError(error);

    return ret;
}

std::size_t wxSerialPort::DoWriteSome(const boost::asio::const_buffer &buffer, int timeout)
{
    std::size_t bytes_written = 0;
    m_io_context.restart();
    DoAsyncWaitThenCancelAsyncIO(timeout);

    m_serialPort.async_write_some(
        buffer,
        [&](const boost::system::error_code &error, std::size_t bytes)
        {
            if (!error)
            {
                m_timer.cancel();
            }
            bytes_written = bytes;
            DoSetLastError(error);
        });

    m_io_context.run();

    return bytes_written;
}

// Port control functions
BOOST_ASIO_SYNC_OP_VOID wxSerialPort::Cancel()
{
    boost::system::error_code error;
    m_serialPort.cancel(error);
    DoSetLastError(error);

    return error;
}

BOOST_ASIO_SYNC_OP_VOID wxSerialPort::Close()
{
    boost::system::error_code error;
    m_serialPort.close(error);
    DoSetLastError(error);

    return error;
}

BOOST_ASIO_SYNC_OP_VOID wxSerialPort::Open(const std::string &device)
{
    m_strPortName = device;
    boost::system::error_code error;
    m_serialPort.open(device, error);
    DoSetLastError(error);

    return error;
}

BOOST_ASIO_SYNC_OP_VOID wxSerialPort::FlushBuffers(Buffers buffers)
{
    boost::system::error_code error;
#ifdef __WXMSW__
    DWORD flags = 0;
    if (buffers & buf_In)
        flags |= PURGE_RXCLEAR;
    if (buffers & buf_Out)
        flags |= PURGE_TXCLEAR;
    if (!::PurgeComm(m_serialPort.native_handle(), flags))
    {
        error = boost::system::error_code(::GetLastError(), boost::asio::error::get_system_category());
    }
#else
    int flags = TCIOFLUSH;
    if (buffers == buf_In)
    {
        flags = TCIFLUSH;
    }
    else if (buffers == buf_Out)
    {
        flags = TCOFLUSH;
    }

    if (tcflush(m_serialPort.native_handle(), flags) == -1)
    {
        error = boost::system::error_code(errno, boost::asio::error::get_system_category());
    }
#endif
    DoSetLastError(error);
    return error;
}

// Helper functions
void wxSerialPort::DoSetTimeout(int timeout)
{
    m_timer.expires_after(timeout == wxTIMEOUT_INFINITE ? std::chrono::steady_clock::duration::max() : std::chrono::milliseconds(timeout));
}

void wxSerialPort::DoAsyncWaitThenCancelAsyncIO(int timeout)
{
    DoSetTimeout(timeout);

    m_timer.async_wait(
        [this](const boost::system::error_code &error)
        {
            if (!error)
            {
                m_serialPort.cancel();
                DoSetLastError(boost::asio::error::timed_out);
            }
        });
}

void wxSerialPort::DoSetLastError(const boost::system::error_code &error)
{
    wxCriticalSectionLocker lock(m_csLastError);
    m_last_error = error;
    OnError();
}

void wxSerialPort::Init()
{
    m_last_error.clear();
}