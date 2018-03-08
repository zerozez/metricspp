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

#ifndef L_METRICSPP_HPP
#define L_METRICSPP_HPP

#include <string>

#include "connector.hpp"
#include "modifier.hpp"

// \brief Library namespace
namespace metricspp {

/** Create Connector Function
 *
 *      Creates new serial db connector's object of \a MetricsConnector
 *      for publishing time values through \a addr api. Connection can be
 *      extended by additionaly passing a \a server_name and a \a tag.
 *      Type of connection depends on availability of certain database and
 *      it plugins or extentions.
 *
 *      \li \c "http://.." for basic rest-api connection
 *      \li ....
 *
 *      \code{.cpp}
 *          auto connector1 =
 *              metricspp::create_connection("http://127.0.0.1:8086",
 *                                           "server01",
 *                                           "app1");
 *          auto connector2 =
 *              metricspp::create_connection("http://127.0.0.1:8086");
 *      \endcode
 *
 *  @see metricspp::Metrics
 *  @param addr Url or address of serial database
 *  @param tags Tags for additional information in db
 *  @return MetrcsConnector object
 */
MetricsConnector create_connection(const std::string &addr,
                                   const std::initializer_list<Tag> &tags = {});

template <class... Tags>
MetricsConnector create_connection(const std::string &addr,
                                   const Tags... tags) {
  return create_connection(addr, {tags...});
}

/** Create Measurement Modificator Function
 *
 *      Create new measurement modificator's object for simplify time data
 *      inputs. It registers measurement \a name and associate input
 *      values as \a vnames. if it parameter empty, will be used \a value
 *      as a name. More information in description of MatricsModifier.
 *
 *      \code{.cpp}
 *          auto mod1 = metricspp::create_measurement("cpu0");
 *
 *          auto mod1 = metricspp::create_measurement("eth0",
 *                                                    "in",
 *                                                    "out");
 *      \endcode
 *
 *  @see metricspp::MetricsModifier
 *  @param name Measurement name
 *  @param vnames Measurement values
 *  @return MetricsModifier object
 *
 */
MetricsModifier create_measurement(
    const std::string &name,
    const std::initializer_list<std::string> &vnames = {});

template <class... Fields>
MetricsModifier create_measurement(const std::string &name,
                                   const Fields &... vnames) {
  return create_measurement(name, {vnames...});
}
}

#endif  // L_METRICSPP_HPP
