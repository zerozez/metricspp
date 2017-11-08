#ifndef L_NETWORKCONNECTOR_H
#define L_NETWORKCONNECTOR_H

#include <string>

#include <curl/curl.h>

namespace metricspp {
class NetworkConnector {
 public:
  NetworkConnector(const std::string &addr = "http:127.0.0.1:8080/");
  virtual ~NetworkConnector();

  bool post(const std::string &data);

 private:
  std::string m_addr;  ///< Full address for publish data

  CURL *m_handle;                 ///< Curl handler
  char m_error[CURL_ERROR_SIZE];  ///< Curl error buffer
};
}

#endif  // L_NETWORKCONNECTOR_H
