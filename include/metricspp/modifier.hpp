#ifndef L_METRICSPP_MODIFIER_HPP
#define L_METRICSPP_MODIFIER_HPP

#include <list>
#include <memory>
#include <string>

// \brief Library namespace
namespace metricspp {
class MetricsModifierPrivate;

/** MetricsModifier class
 *
 *      Class for configuring a data queue for sending in databases. It allows
 *      to simplify input over the same connection without write measurement
 *      and it variables names everytime.
 *
 */
class MetricsModifier {
 public:
  MetricsModifier() = delete;

  /** MetricsModifier constructor
   *
   *    General class constructor for \a measure name and it \a vqueue ,
   *    variable names queue. If vqueue is empty it will add default `value`
   *    name in the list.
   *
   *    Pass in invalid measure or variables names leads to throwing
   *    std::invalid_argument
   *
   * @param measure Measurement name
   * @param vqueue List of measurement's variables. Order of them keeps the same
   *        as it comes in.
   */
  MetricsModifier(const std::string &measure,
                  const std::initializer_list<std::string> &vqueue = {});
  virtual ~MetricsModifier();

  /** Measure method
   *
   *    Get measure's name of this object.
   *
   * @return Name as a string
   */
  std::string measure() const;

  /** Variables name queue
   *
   *    Returns a queue of variables names of the metric
   *
   * @return List of variables names
   */
  std::list<std::string> queue() const;

 private:
  std::string m_measure;           ///< Measure name
  std::list<std::string> m_queue;  ///< Measure's variables queue
};
}

#endif  // L_METRICSPP_MODIFIER_HPP
