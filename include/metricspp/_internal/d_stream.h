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

/** DataStream class
 *
 *      Stream class object returns as the temporary object from
 *      \a MetricsConnector to keep input data for a measurement consistent.
 */
class DataStream {
 public:
  DataStream() = delete;

  /** DataStream Constructor
   *
   *    Creates new object with \a connector as communication pipe over which
   *    it sends formatted data.
   *
   * @param connector Pointer on a valid \a NetworkConnector object
   * @see NetworkConnector
   */
  DataStream(const std::shared_ptr<NetworkConnector> &connector);
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
   *
   *    Inserts name as a \a str for the next value which comes after the call.
   *
   * @param str Name of variable
   *
   * @return Ref for this object
   */
  DataStream &operator<<(const std::string &str);

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
