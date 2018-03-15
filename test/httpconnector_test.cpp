#include <gtest/gtest.h>

#include <metricspp/httpconnector.hpp>

using metricspp::HttpConnector;

class HttpConnectorTest : public ::testing::Test {};

TEST_F(HttpConnectorTest, Constructor) {
  EXPECT_NO_THROW(new HttpConnector());
  EXPECT_NO_THROW(new HttpConnector("http://127.0.0.1/"));
  EXPECT_THROW(new HttpConnector(""), std::invalid_argument);
  EXPECT_THROW(new HttpConnector("n92n09N&%128"), std::invalid_argument);
}

TEST_F(HttpConnectorTest, AddressSet) {
  HttpConnector ctr;
  std::string addr = "http://example.com:544/api";

  EXPECT_NO_THROW(ctr.set_address(addr));
  EXPECT_EQ(ctr.address(), addr);

  EXPECT_NO_THROW(ctr.set_address("localhost"));
  EXPECT_THROW(ctr.set_address(""), std::invalid_argument);
}
