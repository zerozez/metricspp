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
 *      tags if database has it support. They will be attached to every
 *      database commit.
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
   * @param addr Full API address
   * @param tags List of usable tags
   *
   */
  MetricsConnector(const std::string &addr,
                   const std::initializer_list<Tag> &tags = {});

  ~MetricsConnector();

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

  MetricsConnector(const MetricsConnector &cr);
  MetricsConnector &operator=(const MetricsConnector &cr);

 private:
  const std::unique_ptr<metricspp::MetricsConnectorPrivate> m_data;
};
}

#endif  // L_METRICSPP_CONNECTOR_HPP
