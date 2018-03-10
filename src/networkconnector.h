#ifndef L_NETWORKCONNECTOR_H
#define L_NETWORKCONNECTOR_H

#include <string>

#include <curl/curl.h>

namespace metricspp {
/** NetworkConnector class
 *
 *      Network connector class objects communicate with a database
 *      and handle data streams
 */
class NetworkConnector {
 public:
  /** NetworkConnector constructor
   *
   *     Constructor creates a new object with an \a addr to communicate
   *     with
   *
   * @param addr Database address
   */
  NetworkConnector(const std::string &addr = "http:127.0.0.1:8080/");
  virtual ~NetworkConnector();

  /** Post data methid
   *
   *    Sends \a data using post method
   *
   * @param data String of data for send
   *
   * @return \a true on sucess operation
   */
  bool post(const std::string &data);

 private:
  std::string m_addr;  ///< Full address for publish data

  CURL *m_handle;                 ///< Curl handler
  char m_error[CURL_ERROR_SIZE];  ///< Curl error buffer
};
}

#endif  // L_NETWORKCONNECTOR_H
