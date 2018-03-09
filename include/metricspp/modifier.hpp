#ifndef L_METRICSPP_MODIFIER_HPP
#define L_METRICSPP_MODIFIER_HPP

#include <list>
#include <memory>
#include <string>

namespace metricspp {
class MetricsModifierPrivate;
class MetricsModifier {
 public:
  MetricsModifier() = delete;
  MetricsModifier(const std::string &measure,
                  const std::initializer_list<std::string> &vqueue);
  ~MetricsModifier();

  std::string measure() const;

  std::list<std::string> queue() const;

  MetricsModifier(const MetricsModifier &cr);
  MetricsModifier &operator=(const MetricsModifier &cr);

 private:
  const std::unique_ptr<MetricsModifierPrivate> m_data;
};
}

#endif  // L_METRICSPP_MODIFIER_HPP
