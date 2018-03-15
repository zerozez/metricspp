#include <algorithm>
#include <regex>
#include <stdexcept>

#include <metricspp/metric.hpp>

#include "funcollection.h"

using namespace metricspp;

MetricsConnector::MetricsConnector(
    const std::shared_ptr<base::IConnector> &connector,
    std::initializer_list<Tag> tags)
    : m_connector(connector) {
  if (!connector) {
    throw std::invalid_argument("Connector pointer is not valid!");
  }

  std::for_each(tags.begin(), tags.end(), [&](const Tag &tag) {
    if (is_var_valid(tag.first) && is_var_valid(tag.second) &&
        m_tags.find(tag.first) == m_tags.end()) {
      m_tags.emplace(tag);
    }
  });
}

MetricsConnector::~MetricsConnector() {}

std::map<std::string, std::string> MetricsConnector::tags() const {
  return m_tags;
}

_internal::DataStream MetricsConnector::operator<<(const MetricsModifier &mod) {
  auto data = _internal::DataStream(m_connector);

  data.set_measure(mod.measure());
  data.set_tags(m_tags);
  data.set_values_queue(mod.queue());

  return data;
}

_internal::DataStream MetricsConnector::operator<<(const std::string &str) {
  if (!is_var_valid(str)) {
    throw std::invalid_argument("Input measure name is not valid!");
  }
  return operator<<(MetricsModifier(str, {}));
}
