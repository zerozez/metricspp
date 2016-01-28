#include <string>

#include <connection.hpp>
#include <connection_types.hpp>


namespace timestamp
{
    Connection::Connection(timestamp::ConnectionType type)
        : m_type(type)
    {
    }

    Connection::~Connection()
    {
    }

    auto Connection::setAddress(const std::string &addr, const int port) -> void
    {
        // FIXME: add validation for inputs
        m_addr  = addr;
        m_port  = port;
    }

    auto timestamp::Connection::type() const -> ConnectionType
    {
        return m_type;
    }

    auto Connection::addr() const -> std::string
    {
        return m_addr;
    }

    auto Connection::port() const -> int
    {
        return m_port;
    }
}

