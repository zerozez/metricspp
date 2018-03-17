#ifndef L__INTERNAL_DATA_STREAM_H
#define L__INTERNAL_DATA_STREAM_H

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace metricspp {

namespace base {
class IConnector;
}

namespace _internal {
/** DataStream class
 *
 *      Stream class object returns as the temporary object from
 *      \a MetricsConnector to keep input data for a measurement consistent.
 */
class DataStream {
 public:
  using value_storage = std::list<std::pair<std::string, std::string>>;

  DataStream() = delete;

  /** DataStream Constructor
   *
   *    Creates new object with \a connector as communication pipe over which
   *    it sends formatted data.
   *
   * @param connector Pointer on a valid \a NetworkConnector object
   * @see NetworkConnector
   */
  DataStream(const std::shared_ptr<base::IConnector> &connector);
  ~DataStream();

  /** Set Measure name method
   *
   * @param measure Not empty string
   */
  void set_measure(const std::string &measure);

  /** Set queue method
   *
   *    Set list of measurement variables
   *
   * @param queue list of measurement's variables
   */
  void set_values_queue(const std::list<std::string> &queue);

  /** Set tags method
   *
   *    Set measurement tags of a measure.
   *
   * @param tags Dictionary of tags and their values
   */
  void set_tags(const std::map<std::string, std::string> &tags);

  /** Insertion operator

   *    Inserts name as a \a str for the next value which comes after the call.
   *
   * @param str Name of variable
   *
   * @return Ref for this object
   */
  DataStream &operator<<(const std::string &str);

  DataStream &operator<<(const char *data);
  /** Insertion operators(different types)
   *
   *    Inserts numeric value for previous set variable name
   *
   * @param value Data for set
   *
   * @return
   */
  DataStream &operator<<(bool value);
  DataStream &operator<<(short value);
  DataStream &operator<<(double value);
  DataStream &operator<<(float value);
  DataStream &operator<<(long double value);
  DataStream &operator<<(int value);
  DataStream &operator<<(long int value);
  DataStream &operator<<(unsigned value);
  DataStream &operator<<(long unsigned value);

 private:
  /** Set net variable
   *
   *    Sets next variable field with serialized \a value
   *
   * @param value data as a string
   */
  void set_next(const std::string &value);

  /** Set record
   *
   *    Set new record \a value by \a name or update it
   * @param name Record name
   * @param value Record value
   */
  void set_record(const std::string &name, const std::string &value);

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

  std::shared_ptr<base::IConnector> m_connector;  ///< Network connector pointer
};
}
}
#endif  // L__INTERNAL_DATA_STREAM_H
