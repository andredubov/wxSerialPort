////////////////////////////////////////////////////////////////////////////////
// Name:      serialport.h
// Purpose:   Defines wxSerialPort Class
// Author:    Youcef Kouchkar
// Created:   2018-01-08
// Copyright: (c) 2019 Youcef Kouchkar
// License:   MIT License
////////////////////////////////////////////////////////////////////////////////

#ifndef _WX_SERIALPORT_H_
#define _WX_SERIALPORT_H_

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <wx/buffer.h>
#include <wx/string.h>
#include <wx/dir.h>
#include <wx/thread.h>

#define wxTIMEOUT_INFINITE -1

class wxSerialPortBase
{
public:
#ifdef __WXMSW__
    enum BaudRate
    {
        br_75 = 75,
        br_110 = 110,
        br_134_5 = 134,
        br_150 = 150,
        br_300 = 300,
        br_600 = 600,
        br_1200 = 1200,
        br_1800 = 1800,
        br_2400 = 2400,
        br_4800 = 4800,
        br_7200 = 7200,
        br_9600 = 9600,
        br_14400 = 14400,
        br_19200 = 19200,
        br_38400 = 38400,
        br_56000 = 56000,
        br_57600 = 57600,
        br_115200 = 115200,
        br_128000 = 128000
    };
#else
    enum BaudRate
    {
        br_0 = 0,
        br_50 = 50,
        br_75 = 75,
        br_110 = 110,
        br_134 = 134,
        br_150 = 150,
        br_200 = 200,
        br_300 = 300,
        br_600 = 600,
        br_1200 = 1200,
        br_1800 = 1800,
        br_2400 = 2400,
        br_4800 = 4800,
        br_9600 = 9600,
        br_19200 = 19200,
        br_38400 = 38400,
        br_57600 = 57600,
        br_115200 = 115200,
        br_230400 = 230400,
        br_460800 = 460800,
        br_500000 = 500000,
        br_576000 = 576000,
        br_921600 = 921600,
        br_1000000 = 1000000,
        br_1152000 = 1152000,
        br_1500000 = 1500000,
        br_2000000 = 2000000,
        br_2500000 = 2500000,
        br_3000000 = 3000000,
        br_3500000 = 3500000,
        br_4000000 = 4000000
    };
#endif

    enum DataBits
    {
        db_5 = 5,
        db_6 = 6,
        db_7 = 7,
        db_8 = 8
    };
    enum FlowControl
    {
        fc_None,
        fc_Software,
        fc_Hardware
    };
    enum Parity
    {
        p_None,
        p_Odd,
        p_Even
    };
    enum StopBits
    {
        sb_1 = 0,
        sb_1_5 = 1,
        sb_2 = 2
    };
    enum Buffers
    {
        buf_In = 1,
        buf_Out = 2,
        buf_In_Out = 3
    };

    wxSerialPortBase() = default;
    virtual ~wxSerialPortBase() = default;

    static std::vector<wxString> GetPortNames();

protected:
    boost::asio::io_context m_io_context;
};

class wxSerialPort : public wxSerialPortBase
{
    void Init();

    boost::asio::serial_port m_serialPort;
    boost::asio::steady_timer m_timer;
    wxString m_strPortName;
    boost::system::error_code m_last_error;
    wxCriticalSection m_csLastError;

public:
    wxSerialPort();
    explicit wxSerialPort(const std::string &device);
    explicit wxSerialPort(const wxString &device);
    explicit wxSerialPort(const char *device);
    explicit wxSerialPort(const boost::asio::serial_port::native_handle_type &native_serial_port);

    wxSerialPort(const wxSerialPort &other);
    wxSerialPort &operator=(const wxSerialPort &other);

#ifdef BOOST_ASIO_HAS_MOVE
    wxSerialPort(wxSerialPort &&other) noexcept;
    wxSerialPort &operator=(wxSerialPort &&other) noexcept;
#endif

    ~wxSerialPort();

    boost::asio::serial_port &GetSerialPort();
    BOOST_ASIO_SYNC_OP_VOID Assign(const boost::asio::serial_port::native_handle_type &native_serial_port);

    // Synchronous operations
    std::size_t ReadSome(std::string &buffer);
    std::size_t ReadSome(wxCharBuffer &buffer);
    std::size_t ReadSome(void *buffer, std::size_t size);
    std::size_t ReadSome(std::string &buffer, int timeout);
    std::size_t ReadSome(wxCharBuffer &buffer, int timeout);
    std::size_t ReadSome(void *buffer, std::size_t size, int timeout);

    std::size_t WriteSome(const std::string &buffer);
    std::size_t WriteSome(const wxString &buffer);
    std::size_t WriteSome(const wxCharBuffer &buffer);
    std::size_t WriteSome(const void *buffer, std::size_t size);
    std::size_t WriteSome(const std::string &buffer, int timeout);
    std::size_t WriteSome(const wxString &buffer, int timeout);
    std::size_t WriteSome(const wxCharBuffer &buffer, int timeout);
    std::size_t WriteSome(const void *buffer, std::size_t size, int timeout);

    std::size_t Read(std::string &buffer);
    std::size_t Read(wxCharBuffer &buffer);
    std::size_t Read(void *buffer, std::size_t size);
    std::size_t Read(std::string &buffer, int timeout);
    std::size_t Read(wxCharBuffer &buffer, int timeout);
    std::size_t Read(void *buffer, std::size_t size, int timeout);

    std::size_t Write(const std::string &buffer);
    std::size_t Write(const wxString &buffer);
    std::size_t Write(const wxCharBuffer &buffer);
    std::size_t Write(const void *buffer, std::size_t size);
    std::size_t Write(const std::string &buffer, int timeout);
    std::size_t Write(const wxString &buffer, int timeout);
    std::size_t Write(const wxCharBuffer &buffer, int timeout);
    std::size_t Write(const void *buffer, std::size_t size, int timeout);

    std::size_t ReadUntil(std::string &buffer, const std::string &delim);
    std::size_t ReadUntil(wxCharBuffer &buffer, const wxCharBuffer &delim);
    std::size_t ReadUntil(void *buffer, std::size_t size1, const void *delim, std::size_t size2);
    std::size_t ReadUntil(std::string &buffer, const std::string &delim, int timeout);
    std::size_t ReadUntil(wxCharBuffer &buffer, const wxCharBuffer &delim, int timeout);
    std::size_t ReadUntil(void *buffer, std::size_t size1, const void *delim, std::size_t size2, int timeout);

    // Asynchronous operations
    template <typename Handler>
    auto AsyncReadSome(std::string &buffer, Handler &&handler)
        -> decltype(m_serialPort.async_read_some(boost::asio::buffer(buffer), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncReadSome(wxCharBuffer &buffer, Handler &&handler)
        -> decltype(m_serialPort.async_read_some(boost::asio::buffer(buffer.data(), buffer.length()), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncReadSome(void *buffer, std::size_t size, Handler &&handler)
        -> decltype(m_serialPort.async_read_some(boost::asio::buffer(buffer, size), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncWriteSome(const std::string &buffer, Handler &&handler)
        -> decltype(m_serialPort.async_write_some(boost::asio::buffer(buffer), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncWriteSome(const wxString &buffer, Handler &&handler)
        -> decltype(m_serialPort.async_write_some(boost::asio::buffer(buffer.data(), buffer.size()), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncWriteSome(const wxCharBuffer &buffer, Handler &&handler)
        -> decltype(m_serialPort.async_write_some(boost::asio::buffer(buffer.data(), buffer.length()), std::forward<Handler>(handler)));

    template <typename Handler>
    auto AsyncWriteSome(const void *buffer, std::size_t size, Handler &&handler)
        -> decltype(m_serialPort.async_write_some(boost::asio::buffer(buffer, size), std::forward<Handler>(handler)));

    // Port control
    BOOST_ASIO_SYNC_OP_VOID Cancel();
    BOOST_ASIO_SYNC_OP_VOID Close();
    boost::asio::serial_port::executor_type GetExecutor() BOOST_ASIO_NOEXCEPT;

    BOOST_ASIO_SYNC_OP_VOID GetOption(BaudRate &option);
    BOOST_ASIO_SYNC_OP_VOID SetOption(BaudRate option);
    BOOST_ASIO_SYNC_OP_VOID GetOption(DataBits &option);
    BOOST_ASIO_SYNC_OP_VOID SetOption(DataBits option);
    BOOST_ASIO_SYNC_OP_VOID GetOption(FlowControl &option);
    BOOST_ASIO_SYNC_OP_VOID SetOption(FlowControl option);
    BOOST_ASIO_SYNC_OP_VOID GetOption(Parity &option);
    BOOST_ASIO_SYNC_OP_VOID SetOption(Parity option);
    BOOST_ASIO_SYNC_OP_VOID GetOption(StopBits &option);
    BOOST_ASIO_SYNC_OP_VOID SetOption(StopBits option);

    bool IsOpen() const;
    boost::asio::serial_port::native_handle_type GetNativeHandle();
    BOOST_ASIO_SYNC_OP_VOID Open(const std::string &device);
    BOOST_ASIO_SYNC_OP_VOID Open(const wxString &device);
    BOOST_ASIO_SYNC_OP_VOID Open(const char *device);
    BOOST_ASIO_SYNC_OP_VOID ReOpen();
    BOOST_ASIO_SYNC_OP_VOID SendBreak();
    BOOST_ASIO_SYNC_OP_VOID Wait(int timeout);

    wxString GetPortName() const;
    BOOST_ASIO_SYNC_OP_VOID FlushBuffers(Buffers buffers);
    BOOST_ASIO_SYNC_OP_VOID WaitForBuffers(Buffers buffers, int timeout);
    BOOST_ASIO_SYNC_OP_VOID WaitForInBuffer(int timeout);
    BOOST_ASIO_SYNC_OP_VOID WaitForOutBuffer(int timeout);
    void CancelAsyncIO();
    boost::system::error_code GetLastError() const;

protected:
    // Helper functions
    std::size_t DoReadSome(const boost::asio::mutable_buffer &buffer);
    std::size_t DoReadSome(const boost::asio::mutable_buffer &buffer, int timeout);
    std::size_t DoWriteSome(const boost::asio::const_buffer &buffer);
    std::size_t DoWriteSome(const boost::asio::const_buffer &buffer, int timeout);

    std::size_t DoRead(const boost::asio::mutable_buffer &buffer);
    std::size_t DoRead(const boost::asio::mutable_buffer &buffer, int timeout);
    std::size_t DoWrite(const boost::asio::const_buffer &buffer);
    std::size_t DoWrite(const boost::asio::const_buffer &buffer, int timeout);

    std::size_t DoReadUntil(const boost::asio::mutable_buffer &buffer, const boost::asio::const_buffer &delim);
    std::size_t DoReadUntil(const boost::asio::mutable_buffer &buffer, const boost::asio::const_buffer &delim, int timeout);

    void DoSetTimeout(int timeout);
    BOOST_ASIO_SYNC_OP_VOID DoWait(int timeout);
    void DoAsyncWaitThenCancelAsyncIO(int timeout);
    void DoSetLastError(const boost::system::error_code &error);

    std::size_t DoCompletionCondition(const boost::asio::mutable_buffer &buffer,
                                      const boost::asio::const_buffer &delim,
                                      const boost::system::error_code &error,
                                      std::size_t bytes_transferred) const;

    virtual void OnError() {}
};

#endif // _WX_SERIALPORT_H_