#ifndef L_METRICSPP_CONNECTOR_P_H
#define L_METRICSPP_CONNECTOR_P_H

#include <map>
#include <memory>
#include <string>

#include <metricspp/connector.hpp>

namespace metricspp {

class NetworkConnector;
class MetricsConnectorPrivate {
 public:
  MetricsConnectorPrivate() {}
  virtual ~MetricsConnectorPrivate() {}

 private:
  std::shared_ptr<NetworkConnector> m_connector;
  std::map<std::string, std::string> m_tags;

  friend class MetricsConnector;
};
}
#endif  // L_METRICSPP_CONNECTOR_P_H
