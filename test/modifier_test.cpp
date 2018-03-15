#include <gtest/gtest.h>

#include <metricspp/modifier.hpp>

using metricspp::MetricsModifier;

class ModifierTest : public ::testing::Test {};

TEST_F(ModifierTest, Constructor) {
  EXPECT_NO_THROW(new MetricsModifier("data0", {"d0", "d1"}));
  EXPECT_NO_THROW(new MetricsModifier("data0"));
  EXPECT_THROW(new MetricsModifier(""), std::invalid_argument);
  EXPECT_THROW(new MetricsModifier("N(*&@#NN"), std::invalid_argument);
  EXPECT_THROW(new MetricsModifier("data0", {"s(*&NV"}), std::invalid_argument);
}

TEST_F(ModifierTest, Measure) {
  auto mod = MetricsModifier("data0");

  EXPECT_EQ("data0", mod.measure());
}

TEST_F(ModifierTest, Queue) {
  std::initializer_list<std::string> queue = {"d0", "d1", "d3", "d0"};
  auto mod = MetricsModifier("data0", queue);

  EXPECT_EQ(mod.queue(), std::list<std::string>(queue));

  mod = MetricsModifier("data0");
  EXPECT_EQ(mod.queue(), std::list<std::string>{"value"});
}
