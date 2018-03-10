#include <chrono>
#include <sstream>

#include <metricspp/_internal/d_stream.h>
#include <metricspp/base/baseconnector.hpp>

using namespace metricspp::_internal;

DataStream::DataStream(const std::shared_ptr<base::IConnector> &connector) {
  m_connector = connector;
}

DataStream::~DataStream() {
  if (m_connector) {
    m_connector->post(form_data());
  }
}

void DataStream::set_measure(const std::string &measure) {
  if (!measure.empty()) {
    m_measure = measure;
  }
}

void DataStream::set_values_queue(const std::list<std::string> &queue) {
  for (auto &name : queue) {
    m_values.emplace(std::make_pair(name, ""));
  }
  m_pos = m_values.begin();
}

void DataStream::set_tags(const std::map<std::string, std::string> &tags) {
  m_tags.clear();

  for (auto tag = tags.cbegin(); tag != tags.cend(); ++tag) {
    m_tags += tag->first + "=" + tag->second +
              (std::next(tag) == tags.cend() ? "" : ",");
  }
}

DataStream &DataStream::operator<<(const std::string &str) {
  if (m_previous.empty()) {
    m_previous = str;

    if (m_values.find(str) == m_values.end()) {
      m_values.emplace(std::make_pair(str, ""));
    }
  }
  return *this;
}

DataStream &DataStream::operator<<(bool value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(short value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(float value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(double value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long double value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(int value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long int value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(unsigned value) {
  set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long unsigned value) {
  set_next(std::to_string(value));
  return *this;
}

void DataStream::set_next(const std::string &value) {
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

std::string DataStream::form_data() const {
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
