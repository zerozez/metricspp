/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Petr Orlov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>
#include <boost/asio.hpp>

#include "udpconnection.h"


using boost::asio::ip::udp;

namespace timestamp
{
    UDPConnection::UDPConnection()
        : Connection(ConnectionType::UDP)
        , m_io(new boost::asio::io_service())
        , m_endpoint(nullptr)
        , m_socket(new udp::socket(*m_io, udp::endpoint(udp::v4(), 0)))
    {
    }

    UDPConnection::~UDPConnection()
    {
    }

    auto UDPConnection::open() -> bool
    {
        if(!m_endpoint)
        {
            m_endpoint = std::shared_ptr<udp::endpoint>(
                    new udp::endpoint(*udp::resolver(*m_io)
                        .resolve({udp::v4(), this->addr(), std::to_string(this->port())})));
            return true;
        }

        return false;
    }

    auto UDPConnection::close() -> bool
    {
        m_endpoint.reset();

        return true;
    }

    auto UDPConnection::send(const std::string &data) -> void
    {
        if(m_endpoint)
        {
            m_socket->send_to(boost::asio::buffer(data.data(), data.size()), *m_endpoint);
        }
    }
}

