#include <metricspp/metric.hpp>

using namespace metricspp;

MetricsConnector::MetricsConnector(
    const std::shared_ptr<base::IConnector> &connector,
    std::initializer_list<Tag> tags)
    : m_connector(connector), m_tags(tags.begin(), tags.end()) {}

MetricsConnector::~MetricsConnector() {}

_internal::DataStream MetricsConnector::operator<<(const MetricsModifier &mod) {
  auto data = _internal::DataStream(m_connector);

  data.set_measure(mod.measure());
  data.set_tags(m_tags);
  data.set_values_queue(mod.queue());

  return data;
}

_internal::DataStream MetricsConnector::operator<<(const std::string &str) {
  return operator<<(MetricsModifier(str, {}));
}
