#include <gtest/gtest.h>

#include <metricspp/metric.hpp>
#include <metricspp/modifier.hpp>

#include "connector_mock.h"

class MetricTest : public ::testing::Test {
 protected:
  std::shared_ptr<ConnectorMock> ctr;

  virtual void SetUp() {
    ctr = std::make_shared<ConnectorMock>();
  }

  virtual void TearDown() {
    ctr.reset();
  }
};

TEST_F(MetricTest, Constructor) {
  EXPECT_NO_THROW(std::make_shared<metricspp::MetricsConnector>(ctr));
  EXPECT_NO_THROW(std::make_shared<metricspp::MetricsConnector>(
      ctr,
      std::initializer_list<metricspp::Tag>{metricspp::Tag{"name0", "value"}}));
  EXPECT_NO_THROW(std::make_shared<metricspp::MetricsConnector>(
      ctr,
      std::initializer_list<metricspp::Tag>{
          metricspp::Tag{"name0", "value"}, metricspp::Tag{"name1", "value"},
          metricspp::Tag{"name2", "value"}, metricspp::Tag{"name3", "value"}}));
  EXPECT_THROW(std::make_shared<metricspp::MetricsConnector>(nullptr),
               std::invalid_argument);
}

TEST_F(MetricTest, Tags) {
  auto mc = std::make_shared<metricspp::MetricsConnector>(ctr);
  auto tags = mc->tags();
  EXPECT_TRUE(tags.empty());

  mc = std::make_shared<metricspp::MetricsConnector>(
      ctr, std::initializer_list<metricspp::Tag>{
               metricspp::Tag{"name.0", "value"},
               metricspp::Tag{"N*&@N&$$", "1n-0N*1\\value"}});
  tags = mc->tags();
  EXPECT_EQ(tags.size(), 1);
  EXPECT_EQ(tags["name.0"], "value");

  mc = std::make_shared<metricspp::MetricsConnector>(
      ctr,
      std::initializer_list<metricspp::Tag>{metricspp::Tag{"name0", "value"},
                                            metricspp::Tag{"name0", "value2"}});
  tags = mc->tags();

  EXPECT_EQ(tags.size(), 1);
  EXPECT_EQ(tags["name0"], "value");
}

TEST_F(MetricTest, DataInsertion) {
  auto mc = std::make_shared<metricspp::MetricsConnector>(ctr);

  EXPECT_CALL(*ctr, post(::testing::_)).Times(2);

  EXPECT_NO_THROW(mc->operator<<("measure.0") << 1);
  EXPECT_NO_THROW(mc->operator<<(metricspp::MetricsModifier("measure.1")) << 1);
  EXPECT_THROW(mc->operator<<(""), std::invalid_argument);
  EXPECT_THROW(mc->operator<<("qwe=*&^B"), std::invalid_argument);
}
