#ifndef _TEST_CONNECTOR_MOCK_H
#define _TEST_CONNECTOR_MOCK_H value

#include <string>

#include <gmock/gmock.h>

#include <metricspp/base/baseconnector.hpp>

class ConnectorMock : public metricspp::base::IConnector {
 public:
  MOCK_METHOD1(set_address, void(const std::string&));
  MOCK_METHOD1(post, bool(const std::string&));
};

#endif  // _TEST_CONNECTOR_MOCK_H
