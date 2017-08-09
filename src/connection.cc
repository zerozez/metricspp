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
 * The above copyright notice and this permission notice shall be included in
 * all
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

#include <regex>
#include <stdexcept>
#include <string>

#include <connection.hpp>
#include <connection_types.hpp>

namespace timestamp {
Connection::Connection(timestamp::ConnectionType type) : m_type(type) {}

Connection::~Connection() {}

auto Connection::setAddress(const std::string &addr, const int port) -> void {
  if (!std::regex_match(addr, std::regex(exp_ip)) &&
      !std::regex_match(addr, std::regex(exp_addr))) {
    throw std::invalid_argument("[Connection] address invalid : " + addr);
  }

  if (port < 0 || port > 65536) {
    throw std::invalid_argument("[Connection] port invalid : " +
                                std::to_string(port));
  }

  m_addr = addr;
  m_port = port;
}

auto timestamp::Connection::type() const -> ConnectionType { return m_type; }

auto Connection::addr() const -> std::string { return m_addr; }

auto Connection::port() const -> int { return m_port; }
}
