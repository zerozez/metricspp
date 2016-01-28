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

#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <memory>
#include <boost/asio.hpp>

#include <connection.hpp>

namespace timestamp {

    class UDPConnection : public timestamp::Connection
    {
    public:
        UDPConnection();
        virtual ~UDPConnection();

        auto open() -> bool;
        auto close() -> bool;

        auto send(const std::string &data) -> void;

    private:
        std::shared_ptr<boost::asio::io_service>        m_io;
        std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
        std::shared_ptr<boost::asio::ip::udp::socket>   m_socket;

    };
}

#endif // UDPCONNECTION_H

