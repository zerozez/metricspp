#include <metricspp/modifier.hpp>

#include "modifier_p.h"

using namespace metricspp;

MetricsModifier::MetricsModifier(
    const std::string &measure,
    const std::initializer_list<std::string> &vqueue)
    : m_data(new MetricsModifierPrivate()) {
  m_data->m_measure = measure;
  m_data->m_queue = vqueue.size() == 0 ? std::list<std::string>{"value"}
                                       : std::list<std::string>(vqueue);
}

MetricsModifier::~MetricsModifier() {}

std::string MetricsModifier::measure() const {
  return m_data->m_measure;
}

std::list<std::string> MetricsModifier::queue() const {
  return m_data->m_queue;
}

MetricsModifier::MetricsModifier(const MetricsModifier &cr)
    : m_data(new MetricsModifierPrivate()) {
  operator=(cr);
}

MetricsModifier &MetricsModifier::operator=(const MetricsModifier &cr) {
  *m_data = *cr.m_data;
}
