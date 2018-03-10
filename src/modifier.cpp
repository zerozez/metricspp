#include <metricspp/modifier.hpp>

using namespace metricspp;

MetricsModifier::MetricsModifier(
    const std::string &measure,
    const std::initializer_list<std::string> &vqueue)
    : m_measure(measure) {
  m_queue = vqueue.size() == 0 ? std::list<std::string>{"value"}
                               : std::list<std::string>(vqueue);
}

MetricsModifier::~MetricsModifier() {}

std::string MetricsModifier::measure() const {
  return m_measure;
}

std::list<std::string> MetricsModifier::queue() const {
  return m_queue;
}
