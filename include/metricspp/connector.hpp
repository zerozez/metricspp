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
