#ifndef L_METRICSPP_HPP
#define L_METRICSPP_HPP

#include <string>

#include "base/baseconnector.hpp"
#include "metric.hpp"
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
template <class Connector, class... Tags>
MetricsConnector create_connection(const std::shared_ptr<Connector> &connector,
                                   const Tags... tags) {
  return metricspp::MetricsConnector(connector, {tags...});
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
template <class... Fields>
MetricsModifier create_measurement(const std::string &name,
                                   const Fields &... vnames) {
  return MetricsModifier(name, {vnames...});
}
}

#endif  // L_METRICSPP_HPP
