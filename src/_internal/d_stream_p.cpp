#include <chrono>
#include <sstream>

#include "d_stream_p.h"

using namespace metricspp::_internal;

void DataStreamPrivate::set_next(const std::string &value) {
  if (!m_previous.empty()) {
    m_values[m_previous] = value;
    m_previous.clear();
    return;
  }

  if (m_pos != m_values.end()) {
    if (m_pos->second.empty()) {
      m_pos->second = value;
    }
    ++m_pos;
  }
}

std::string DataStreamPrivate::form_data() const {
  std::stringstream out;
  out << m_measure << (m_tags.empty() ? "" : ",") << m_tags << " ";

  bool first = true;
  for (auto value = m_values.cbegin(); value != m_values.cend(); ++value) {
    if (!value->second.empty()) {
      out << (first ? "" : ",") << value->first << "=" << value->second;

      if (first) {
        first = false;
      }
    }
  }

  out << " "
      << std::chrono::nanoseconds(
             std::chrono::system_clock::now().time_since_epoch())
             .count();

  return out.str();
}
