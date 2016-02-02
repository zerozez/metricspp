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

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>

#include <connection_types.hpp>


namespace timestamp {
    class Connection {
    public:
        Connection(ConnectionType type = ConnectionType::HTTP_API);
        virtual ~Connection();

        auto setAddress(const std::string &addr, const int port) -> void;
        auto type() const -> ConnectionType;

        virtual bool open() = 0;
        virtual bool close() = 0;
        virtual void send(const std::string &data) = 0;

    protected:
        auto addr() const -> std::string;
        auto port() const -> int;

    private:
        int             m_port;
        std::string     m_addr;
        ConnectionType  m_type;

        const std::string   exp_ip  = "^(\?:(\?:25[0-5]|2[0-4][0-9]|[01]"
                                      "\?[0-9][0-9]\?)\\.){3}(\?:25[0-5]|"
                                      "2[0-4][0-9]|[01]\?[0-9][0-9]\?)$";

        const std::string   exp_addr = "^(\?:(\?:[a-zA-Z0-9]|[a-zA-Z0-9]"
                                       "[a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*"
                                       "(\?:[A-Za-z0-9]|[A-Za-z0-9]"
                                       "[A-Za-z0-9\\-]*[A-Za-z0-9])$";

    };
}

#endif // CONNECTION_HPP

