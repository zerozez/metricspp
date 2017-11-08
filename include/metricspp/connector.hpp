/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Petr Orlov <zfmeze@gmail.com>
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

#ifndef L_METRICSPP_CONNECTOR_HPP
#define L_METRICSPP_CONNECTOR_HPP

#include <memory>
#include <string>
#include <utility>

#include "modifier.hpp"

#include "_internal/d_stream.h"

// \brief Library namespace
namespace metricspp {

using Tag = std::pair<std::string, std::string>;

class MetricsModifier;
class MetricsConnectorPrivate;

/** MetricsConnector class
 *
 *      General working class. Object of this class primary uses for
 *      sending metrics in series databases. Can be extended with different
 *      tags if database has it support.
 *
 */
class MetricsConnector {
 public:
  MetricsConnector() = delete;

  /** MetricsConnector constructor
   *
   *    Specified class constructor for the class' object with \a addr
   *    as address of specified API and list of \a tags for future
   *    usage
   *
   *    Address, tags names and tags values cannot be empty, it exception other
   *    way
   *
   * @param addr Full API address
   * @param tags List of usable tags
   *
   */
  MetricsConnector(const std::string &addr,
                   const std::initializer_list<Tag> &tags = {});

  ~MetricsConnector();

  _internal::DataStream operator<<(const MetricsModifier &mod);
  _internal::DataStream operator<<(const std::string &str);

  MetricsConnector(const MetricsConnector &cr);
  MetricsConnector &operator=(const MetricsConnector &cr);

 private:
  const std::unique_ptr<metricspp::MetricsConnectorPrivate> m_data;
};
}

#endif  // L_METRICSPP_CONNECTOR_HPP
