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
#include <stdexcept>

#include <cfactory.hpp>
#include <idatabase.hpp>
#include <connection.hpp>

// pre-register includes
#include "influxdb.h"
#include "udpconnection.h"

namespace timestamp
{
    CFactory::CFactory()
        : enable_shared_from_this()
    {
        // InfluxDB UDP connection
        // FIXME: should be map of types (connect/dbwrapper)
        m_regs["influx.udp"] = "in";

        // FIXME: Must not to preset on exactly connection type
        m_db        = std::shared_ptr<IDatabase>(new InfluxDB());
        m_connect   = std::shared_ptr<Connection>(new UDPConnection());
    }

    CFactory::~CFactory()
    {
    }

    auto CFactory::registerConnection(const std::string &regName,
                                      const IDatabase *db,
                                      const Connection *connection) -> void
    {
        // TODO: With existing regName shoud we just rewrite db and connection?
        if(m_regs.find(regName) != m_regs.end())
            throw std::invalid_argument("That name already registered: " + regName);

        // FIXME: no current registers
    }

    auto CFactory::setupConnection(const std::string &address,
                                   const int port,
                                   const std::string &regName) -> void
    {
        if(m_regs.find(regName) == m_regs.end())
            throw std::invalid_argument("No Registered connection found: " + regName);

        //FIXME: add check for valid ip addr and port. Here or in connection
        m_connect->setAddress(address, port);
        m_connect->open();
    }

    auto CFactory::send(const UnifiedData &data) -> void
    {
        // TODO: Think about THAT call. Can we make it more attractive?
        m_connect->send(m_db->format(data, m_connect->type()));
    }
}

