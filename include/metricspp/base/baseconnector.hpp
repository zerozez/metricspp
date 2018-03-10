#ifndef _BASE_BASECONNECTOR_
#define _BASE_BASECONNECTOR_

#include <string>

namespace metricspp {
namespace base {

/** IConnector interface class
 *
 *      Represents a data interface for database. All custom connectors
 *      must be derived from this class.
 */
class IConnector {
 public:
  /** Post data method
   *
   *    Sends \a data using post method
   *
   * @param data String of data for send
   *
   * @return \a true on sucess operation
   */
  virtual bool post(const std::string &data) = 0;
};
}
}
#endif  // ifndef _BASE_BASECONNECTOR_
