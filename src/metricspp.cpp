#include <metricspp/metricspp.hpp>

using namespace metricspp;

MetricsConnector metricspp::create_connection(
    const std::string &addr, const std::initializer_list<Tag> &tags) {
  return MetricsConnector(addr, tags);
}

MetricsModifier metricspp::create_measurement(
    const std::string &name, const std::initializer_list<std::string> &vnames) {
  return MetricsModifier(name, vnames);
}
