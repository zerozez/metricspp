#ifndef L__INTERNAL_DATA_STREAM_P_H
#define L__INTERNAL_DATA_STREAM_P_H

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace metricspp {
class NetworkConnector;

namespace _internal {
class DataStreamPrivate {
  void set_next(const std::string &value);

  std::string form_data() const;

  std::string m_previous;
  std::string m_measure;
  std::string m_tags;
  std::unordered_map<std::string, std::string> m_values;
  std::unordered_map<std::string, std::string>::iterator m_pos;

  std::shared_ptr<NetworkConnector> m_connector;

  friend class DataStream;
};
}
}
#endif  // L__INTERNAL_DATA_STREAM_P_H
