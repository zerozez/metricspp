#include <metricspp/_internal/d_stream.h>

#include "../networkconnector.h"
#include "d_stream_p.h"

using namespace metricspp::_internal;

DataStream::DataStream(const std::shared_ptr<NetworkConnector> &connector)
    : m_data(new DataStreamPrivate()) {
  m_data->m_connector = connector;
}

DataStream::~DataStream() {
  if (m_data->m_connector) {
    m_data->m_connector->post(m_data->form_data());
  }
}

void DataStream::set_measure(const std::string &measure) {
  if (!measure.empty()) {
    m_data->m_measure = measure;
  }
}

void DataStream::set_values_queue(const std::list<std::string> &queue) {
  for (auto &name : queue) {
    m_data->m_values.emplace(std::make_pair(name, ""));
  }
  m_data->m_pos = m_data->m_values.begin();
}

void DataStream::set_tags(const std::map<std::string, std::string> &tags) {
  m_data->m_tags.clear();

  for (auto tag = tags.cbegin(); tag != tags.cend(); ++tag) {
    m_data->m_tags += tag->first + "=" + tag->second +
                      (std::next(tag) == tags.cend() ? "" : ",");
  }
}

DataStream &DataStream::operator<<(const std::string &str) {
  if (m_data->m_previous.empty()) {
    m_data->m_previous = str;

    if (m_data->m_values.find(str) == m_data->m_values.end()) {
      m_data->m_values.emplace(std::make_pair(str, ""));
    }
  }
  return *this;
}

DataStream &DataStream::operator<<(bool value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(short value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(float value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(double value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long double value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(int value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long int value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(unsigned value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream &DataStream::operator<<(long unsigned value) {
  m_data->set_next(std::to_string(value));
  return *this;
}

DataStream::DataStream(const DataStream &stream) : DataStream(nullptr) {
  this->operator=(stream);
}

DataStream &DataStream::operator=(const DataStream &in) {
  if (&in != this) {
    *m_data = *in.m_data;
  }
  return *this;
}
