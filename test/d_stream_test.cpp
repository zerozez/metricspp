#include <functional>
#include <string>

#include <gtest/gtest.h>

#include <metricspp/_internal/d_stream.h>

#include "connector_mock.h"

using ::testing::StartsWith;
using ::testing::_;

using metricspp::_internal::DataStream;

class DataStreamTest : public ::testing::Test {
 protected:
  std::shared_ptr<ConnectorMock> ctr;
  std::string measure = "test.0";

  virtual void SetUp() {
    ctr = std::make_shared<ConnectorMock>();
  }

  virtual void TearDown() {
    ctr.reset();
  }

  void test_ouput(
      const std::function<void(const std::shared_ptr<DataStream> &,
                               const std::shared_ptr<ConnectorMock> &)> &fn) {
    auto connector = std::make_shared<ConnectorMock>();
    auto stream = std::make_shared<DataStream>(connector);

    fn(stream, connector);
  }
};

TEST_F(DataStreamTest, Constructor) {
  EXPECT_NO_THROW(new DataStream(std::make_shared<ConnectorMock>()));
  EXPECT_THROW(new DataStream(nullptr), std::invalid_argument);
}

TEST_F(DataStreamTest, SetTags) {
  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + " ")));

    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + ",tag0=value0,tag1=value1")));
    st->set_tags({{"tag0", "value0"}, {"tag1", "value1"}});

    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + ",valid=value0 ")));
    st->set_tags({{"valid", "value0"},
                  {"ta%##$ag0", "value0"},
                  {"tag7", "N*&#vb1"},
                  {"tag1", ""},
                  {"", "value1"},
                  {"valid", "value2"}});

    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });
}

TEST_F(DataStreamTest, SetMeasure) {
  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + " ")));
    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + " ")));
    st->set_measure("v1");
    st->set_measure("v2");
    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(_)).Times(0);
    st->set_values_queue({"value"});
    *st << 1;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(_)).Times(0);
    st->set_measure("N(&98273)(*!@");
    st->set_values_queue({"value"});
    *st << 1;
  });
}

TEST_F(DataStreamTest, SetQueue) {
  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + " value=1 ")));
    st->set_measure(measure);
    st->set_values_queue({"value"});
    *st << 1;
  });
  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(_)).Times(0);
    st->set_measure(measure);
    st->set_values_queue({"value"});
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(StartsWith(measure + " value0=1,value2=5 ")));
    st->set_measure(measure);
    st->set_values_queue({"value0"});
    st->set_values_queue({"value0", "value2", "value0"});
    *st << 1 << 5 << 4;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(_)).Times(0);
    st->set_measure(measure);
    st->set_values_queue({"", "*&^V@C"});
    *st << 1 << 5;
  });

  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(*cn, post(_)).Times(0);
    st->set_measure(measure);
    *st << 1;
  });
}

TEST_F(DataStreamTest, Insertion) {
  test_ouput([&](const std::shared_ptr<DataStream> &st,
                 const std::shared_ptr<ConnectorMock> &cn) {
    EXPECT_CALL(
        *cn,
        post(StartsWith(measure + " value0=1,value2=5.55,value5=1,value10=-0."
                                  "4441,value12=0,value13=2,value14=3.3,"
                                  "value15=-15,value16=20,value17=12345678 ")));
    st->set_measure(measure);
    st->set_values_queue({"value0", "value2", "value5"});
    *st << 1 << 5.55 << true << "value10" << -0.4441 << "value11"
        << "value12" << 0 << "q<F10>N" << 5 << "value13" << short(2)
        << "value14" << (long double)(3.3) << "value15" << (long int)(-15)
        << "value16" << (unsigned)(20) << "value17"
        << (long unsigned)(12345678);
  });
}
