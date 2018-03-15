#ifndef _METRICSPP_FUNCOLLECTION_H
#define _METRICSPP_FUNCOLLECTION_H

#include <iomanip>
#include <sstream>
#include <string>

namespace metricspp {
/** Check variable function
 *
 *      Verifies if input \a varuable is valid to use
 *      as a name or a value of measurement.
 *
 *      A value must contains only letters, numbers, dot(.) signes and/or
 *      underline(_) signes
 *
 * @param variable input text variable
 * @return true if conditions meet
 */
bool is_var_valid(const std::string &variable);

template <class T>
std::string to_string(const T &value) {
  std::stringstream out;
  out.unsetf(std::ios::floatfield);
  out << std::setprecision(10) << value;

  return out.str();
}
}

#endif  // ifndef _METRICSPP_FUNCOLLECTION_H
