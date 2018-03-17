#ifndef L_NETWORKCONNECTOR_H
#define L_NETWORKCONNECTOR_H

#include <string>

#include "base/baseconnector.hpp"

namespace metricspp {
/** HttpConnector class
 *
 *      Network connector class objects communicate with a database
 *      and handle data streams
 */
class HttpConnector : public base::IConnector {
 public:
  HttpConnector();

  /** HttpConnector constructor
   *
   *     Constructor creates a new object with an \a addr to communicate
   *     with.
   *
   * @param addr Database address. Address must be valid http address otherwise
   *    it throw std::invalid_argument exception.
   */
  HttpConnector(const std::string &addr);

  virtual ~HttpConnector();

  /** Post data method
   *
   *    Reimplemented method.
   *
   * @param data
   * @see base::IConnector::post
   *
   * @return \a true on sucess operation
   */
  bool post(const std::string &data) override;

  /** Set adress
   *
   *    Set new database address. Acts like if in constructor pass an address
   *
   * @param addr Valid server address.
   */
  void set_address(const std::string &addr);

  /** Get address
   *
   *    Returns current usable address.
   *
   * @return Domain or ip address
   */
  std::string address() const;

 private:
  std::string m_addr;   ///< Usable address
  std::string m_error;  ///< Curl error buffer

  void *m_handle;  ///< Curl handler
};
}

#endif  // L_NETWORKCONNECTOR_H
