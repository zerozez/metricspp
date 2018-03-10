#ifndef L_METRICSPP_MODIFIER_P_H
#define L_METRICSPP_MODIFIER_P_H

#include <list>
#include <string>

namespace metricspp {
class MetricsModifierPrivate {
 public:
  MetricsModifierPrivate() {}
  virtual ~MetricsModifierPrivate() {}

 private:
  std::string m_measure;           ///< Measure name
  std::list<std::string> m_queue;  ///< Measure's variables queue

  friend class MetricsModifier;
};
}
#endif  // L_METRICSPP_MODIFIER_P_H
