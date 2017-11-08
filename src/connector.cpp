#include <metricspp/connector.hpp>

#include "connector_p.h"
#include "networkconnector.h"

using namespace metricspp;

MetricsConnector::MetricsConnector(const std::string &addr,
                                   const std::initializer_list<Tag> &tags)
    : m_data(new MetricsConnectorPrivate()) {
  m_data->m_connector = std::make_shared<NetworkConnector>(addr);

  for (auto &value : tags) {
    m_data->m_tags.emplace(value);
  }
}

MetricsConnector::~MetricsConnector() {}

_internal::DataStream MetricsConnector::operator<<(const MetricsModifier &mod) {
  auto data = _internal::DataStream(m_data->m_connector);

  data.set_measure(mod.measure());
  data.set_tags(m_data->m_tags);
  data.set_values_queue(mod.queue());

  return data;
}

_internal::DataStream MetricsConnector::operator<<(const std::string &str) {
  return operator<<(MetricsModifier(str, {}));
}

MetricsConnector::MetricsConnector(const MetricsConnector &cr)
    : m_data(new MetricsConnectorPrivate()) {
  this->operator=(cr);
}

MetricsConnector &MetricsConnector::operator=(const MetricsConnector &cr) {
  m_data->m_connector =
      std::make_shared<NetworkConnector>(*cr.m_data->m_connector);
  m_data->m_tags = cr.m_data->m_tags;

  return *this;
}
