#ifndef L_METRICSPP_CONNECTOR_HPP
#define L_METRICSPP_CONNECTOR_HPP

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "base/baseconnector.hpp"
#include "modifier.hpp"

#include "_internal/d_stream.h"

// \brief Library namespace
namespace metricspp {

using Tag = std::pair<std::string, std::string>;

/** MetricsConnector class
 *
 *      General working class. Object of this class primary uses for
 *      sending metrics in series databases. Can be extended with different
 *      tags if database has it support. They will be attached to every
 *      database commit.
 *
 *      Connector must be based on IConnector
 */
class MetricsConnector {
 public:
  MetricsConnector() = delete;

  /** MetricsConnector constructor
   *
   *    Specified class constructor for the class' object with \a connector
   *    as access point, through all data will flow, and list of \a tags for
   *    future usage. Tags must only contain letters and/or numbers without
   *
   * @param connector Shared pointer to connector. If pointer is invalid,
   *    invalid_argument will be throw as exception
   * @param tags List of usable tags
   * @see base::IConnector
   *
   */
  MetricsConnector(const std::shared_ptr<base::IConnector> &connector,
                   std::initializer_list<Tag> tags = {});

  virtual ~MetricsConnector();

  /** Get Metric Tags
   *
   *    Returns tags and values for this metric.
   *
   * @return map of tags
   */
  std::map<std::string, std::string> tags() const;

  /** Insertion Operator
   *
   *    Insertion operator for \a MetricsModifier object. Allows to
   *    syncronize input data with \a mod data queue and send it to
   *    database.
   *
   *    All future insertion go into _internal::DataStream as regular
   *    values.
   *
   * @param mod MetricsModifier object
   * @see MetricsModifier
   * @see _internal::DataStream
   *
   * @return Temporary DataStream object of current data stream
   */
  _internal::DataStream operator<<(const MetricsModifier &mod);

  /** Insertion Operator
   *
   *    Insertion operator for starting a values insertion for a measurement
   *    name as \str. With operator is guaratees that all data which comes
   *    in this stream will be recorded into \str measurement. If next comming
   *    value is not a name of variable it will be stored with default
   *    name(depends on db type).
   *
   *    All future insertion go into _internal::DataStream as regular
   *    values.
   *
   * @param str Stored variable name
   * @see _internal::DataStream
   *
   * @return Temporary DataStream object of current data stream
   */
  _internal::DataStream operator<<(const std::string &str);

 private:
  std::shared_ptr<base::IConnector> m_connector;  // Network Connector
  std::map<std::string, std::string> m_tags;      // Measurement tags
};
}

#endif  // L_METRICSPP_CONNECTOR_HPP
