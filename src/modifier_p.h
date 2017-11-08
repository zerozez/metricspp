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
  std::string m_measure;
  std::list<std::string> m_queue;

  friend class MetricsModifier;
};
}
#endif  // L_METRICSPP_MODIFIER_P_H
