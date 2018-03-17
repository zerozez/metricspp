#ifndef _METRICSPP_FUNCOLLECTION_H
#define _METRICSPP_FUNCOLLECTION_H

#include <limits>
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

/** Number-2-string convertor
 *
 *      Conver a number of input \a Type to a string. Maximum limit of
 *      exponenta size is set to 15, greater when that makes float point
 *      nubmers not really predictible because of the nature of float numbers.
 * @param value
 *
 * @return Numer as a string
 */
template <class T>
std::string to_string(const T &value) {
  std::stringstream out;
  const static size_t restrictrion = 15;  // Maximum number of the exp. tail
  out.unsetf(std::ios::floatfield);
  out.precision(restrictrion >= std::numeric_limits<T>::digits10
                    ? std::numeric_limits<T>::digits10
                    : restrictrion);
  out << value;

  return out.str();
}
}

#endif  // ifndef _METRICSPP_FUNCOLLECTION_H
