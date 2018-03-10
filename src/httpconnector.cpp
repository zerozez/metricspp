#include <metricspp/httpconnector.hpp>

#include <curl/curl.h>

using namespace metricspp;

HttpConnector::HttpConnector()
    : m_error(CURL_ERROR_SIZE, '\0'), m_handle(NULL) {
  m_handle = curl_easy_init();

  if (m_handle) {
    auto version_info = curl_version_info(CURLVERSION_NOW);
    auto version = std::string{"curl/"} + std::string{version_info->version};

    curl_easy_setopt(m_handle, CURLOPT_USERAGENT, version.data());
    curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(m_handle, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(m_handle, CURLOPT_ERRORBUFFER, m_error.data());
    curl_easy_setopt(m_handle, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(m_handle, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(m_handle, CURLOPT_TIMEOUT_MS, 1000);

#if LIBCURL_VERSION_MAJOR >= 7
#if LIBCURL_VERSION_MINOR >= 25
#if LIBCURL_VERSION_PATCH >= 0
    curl_easy_setopt(m_handle, CURLOPT_TCP_KEEPALIVE, 1L);
#endif
#endif
#endif
  }
}

HttpConnector::HttpConnector(const std::string &addr) : HttpConnector() {
  set_address(addr);
}

HttpConnector::~HttpConnector() {
  curl_easy_cleanup(m_handle);
}

bool HttpConnector::post(const std::string &data) {
  if (m_handle == NULL) {
    return false;
  }

  curl_easy_setopt(m_handle, CURLOPT_POSTFIELDS, data.c_str());

  if (curl_easy_perform(m_handle) == CURLE_OK) {
    return true;
  }

  return false;
}

void HttpConnector::set_address(const std::string &addr) {
  m_addr = addr;
  curl_easy_setopt(m_handle, CURLOPT_URL, addr.c_str());
}

std::string HttpConnector::address() const {
  return m_addr;
}
