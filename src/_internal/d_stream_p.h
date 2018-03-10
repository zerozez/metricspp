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
  using value_storage = std::unordered_map<std::string, std::string>;

  /** Set net variable
   *
   *    Sets next variable field with serialized \a value
   *
   * @param value data as a string
   */
  void set_next(const std::string &value);

  /** Format data method
   *
   *    Forms a string for send from set of variables,tags and the measure name.
   *
   * @return Formatted string
   */
  std::string form_data() const;

  std::string m_previous;  ///< Previusly set variable name
  std::string m_measure;   ///< Measure name
  std::string m_tags;      ///< Measure tags

  value_storage m_values;         ///< Measure values
  value_storage::iterator m_pos;  ///< Current position of values fill procedure

  std::shared_ptr<NetworkConnector> m_connector;  ///< Network connector pointer

  friend class DataStream;
};
}
}
#endif  // L__INTERNAL_DATA_STREAM_P_H
