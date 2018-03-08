#ifndef L__INTERNAL_DATA_STREAM_H
#define L__INTERNAL_DATA_STREAM_H

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>

namespace metricspp {
class NetworkConnector;

namespace _internal {
class DataStreamPrivate;
class DataStream {
 public:
  DataStream() = delete;
  DataStream(const std::shared_ptr<NetworkConnector> &connector);
  ~DataStream();

  void set_measure(const std::string &measure);
  void set_values_queue(const std::list<std::string> &queue);
  void set_tags(const std::map<std::string, std::string> &tags);

  DataStream &operator<<(const std::string &str);

  DataStream &operator<<(bool value);
  DataStream &operator<<(short value);
  DataStream &operator<<(float value);
  DataStream &operator<<(double value);
  DataStream &operator<<(long double value);
  DataStream &operator<<(int value);
  DataStream &operator<<(long int value);
  DataStream &operator<<(unsigned value);
  DataStream &operator<<(long unsigned value);

  DataStream(const DataStream &stream);
  DataStream &operator=(const DataStream &in);

 private:
  const std::unique_ptr<DataStreamPrivate> m_data;
};
}
}
#endif  // L__INTERNAL_DATA_STREAM_H
