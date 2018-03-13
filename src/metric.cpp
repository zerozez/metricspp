#include <algorithm>
#include <regex>
#include <stdexcept>

#include <metricspp/metric.hpp>

using namespace metricspp;

MetricsConnector::MetricsConnector(
    const std::shared_ptr<base::IConnector> &connector,
    std::initializer_list<Tag> tags)
    : m_connector(connector) {
  if (!connector) {
    throw std::invalid_argument("Connector pointer is not valid!");
  }

  std::for_each(tags.begin(), tags.end(), [&](const Tag &tag) {
    if (is_valid(tag.first) && is_valid(tag.second) &&
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
  if (!is_valid(str)) {
    throw std::invalid_argument("Input measure name is not valid!");
  }
  return operator<<(MetricsModifier(str, {}));
}

bool MetricsConnector::is_valid(const std::string &input) const {
  static const std::regex tag_regex("^[\\w\\.]+$");
  return std::regex_match(input, tag_regex);
}
