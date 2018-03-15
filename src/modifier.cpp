#include <stdexcept>

#include <metricspp/modifier.hpp>

#include "funcollection.h"

using namespace metricspp;

MetricsModifier::MetricsModifier(
    const std::string &measure,
    const std::initializer_list<std::string> &vqueue)
    : m_measure(measure) {
  if (!is_var_valid(measure)) {
    throw std::invalid_argument("Invalid measure name");
  }

  for (auto &value : vqueue) {
    if (!is_var_valid(value)) {
      throw std::invalid_argument("Invalid variable name");
    }
    m_queue.emplace_back(value);
  }

  if (m_queue.empty()) {
    m_queue.emplace_back("value");
  }
}

MetricsModifier::~MetricsModifier() {}

std::string MetricsModifier::measure() const {
  return m_measure;
}

std::list<std::string> MetricsModifier::queue() const {
  return m_queue;
}
