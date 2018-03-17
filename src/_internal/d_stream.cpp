#include <algorithm>
#include <chrono>
#include <map>
#include <sstream>

#include <metricspp/_internal/d_stream.h>
#include <metricspp/base/baseconnector.hpp>

#include "../funcollection.h"

using namespace metricspp::_internal;

DataStream::DataStream(const std::shared_ptr<base::IConnector> &connector)
    : m_connector(connector), m_pos(m_values.end()) {
  if (!connector) {
    throw std::invalid_argument("Input connector pointer is invalid");
  }
}

DataStream::~DataStream() {
  if (m_connector) {
    auto data = form_data();
    if (!data.empty()) {
      m_connector->post(data);
    }
  }
}

void DataStream::set_measure(const std::string &measure) {
  if (is_var_valid(measure)) {
    m_measure = measure;
  }
}

void DataStream::set_values_queue(const std::list<std::string> &queue) {
  m_values.clear();

  for (auto &name : queue) {
    if (is_var_valid(name)) {
      set_record(name, "");
    }
  }
  m_pos = m_values.begin();
}

void DataStream::set_tags(const std::map<std::string, std::string> &tags) {
  m_tags.clear();

  for (auto tag = tags.cbegin(); tag != tags.cend(); ++tag) {
    if (is_var_valid(tag->first) && is_var_valid(tag->second)) {
      m_tags += tag->first + "=" + tag->second +
                (std::next(tag) == tags.cend() ? "" : ",");
    }
  }
}

DataStream &DataStream::operator<<(const std::string &str) {
  if (is_var_valid(str)) {
    m_previous = str;
  }
  return *this;
}

DataStream &DataStream::operator<<(const char *data) {
  return this->operator<<(std::string(data));
}

DataStream &DataStream::operator<<(bool value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(short value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(double value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(float value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long double value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(int value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long int value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(unsigned value) {
  set_next(to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long unsigned value) {
  set_next(to_string(value));
  return *this;
}

void DataStream::set_next(const std::string &value) {
  if (!m_previous.empty()) {
    set_record(m_previous, value);
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

void DataStream::set_record(const std::string &name, const std::string &value) {
  auto pos = std::find_if(
      m_values.begin(), m_values.end(),
      [name](const value_storage::value_type &it) { return it.first == name; });

  if (pos == m_values.end()) {
    m_values.emplace_back(std::make_pair(name, value));
  } else {
    (pos->second = value);
  }
}

std::string DataStream::form_data() const {
  std::stringstream out;

  // No need to send somthing if name is empty or it values
  if (m_measure.empty() || m_values.empty()) {
    return "";
  }

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

  // No need to send somthing if we put nothing as a value
  if (first) {
    return "";
  }

  out << " "
      << std::chrono::nanoseconds(
             std::chrono::system_clock::now().time_since_epoch())
             .count();

  return out.str();
}
