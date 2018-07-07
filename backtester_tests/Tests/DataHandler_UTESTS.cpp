//
// Created by Evan Kirkiles on 7/5/18.
//

#include <gtest/gtest.h>
#include "Infrastructure/data.hpp"

// Data Handler test fixture
class DataHandlerFixture : public ::testing::Test {
protected:
    void TearDown() override {}
    void SetUp() override {}

public:

    // Empty constructor
    DataHandlerFixture() : Test() {};
    // Destructor
    ~DataHandlerFixture() override = default;
};

// Tests whether the Static Data Handler fully loads the history when buildHistory() is called
TEST(DataHandlerFixture, static_buildshistory) {

    // Instance of the Data Handler
    StaticDataHandler sdh;
    sdh.buildHistory({"AAPL", "SPY"}, "2017-07-03", "2017-07-10", "1d", {"open", "close"}, 3);

    EXPECT_EQ(get_epoch_time("2017-06-30"), *sdh.fullhistory.dates.begin());
    EXPECT_EQ(get_epoch_time("2017-07-10"), sdh.fullhistory.dates.back());
}

// Tests whether the Static Data Handler correctly pulls the right period in history when history() is called
TEST(DataHandlerFixture, static_historyfunction) {

    // Instance of the Data Handler
    StaticDataHandler sdh;
    sdh.buildHistory({"AAPL", "SPY"}, "2017-07-03", "2017-07-10", "1d", {"open", "close"}, 6);

    // Call the history function into a bardata object
    BarData bd = sdh.history(get_epoch_time("2017-07-09"), {"AAPL","SPY"}, {"open"}, "1d", 6);
    BarData bd2 = sdh.history(get_epoch_time("2017-07-09"), {"SPY"}, {"close"}, "1d", 4);

    // Check beginning and end of the BarData dates
    EXPECT_EQ(get_epoch_time("2017-07-03"), *bd.dates.begin());
    EXPECT_EQ(get_epoch_time("2017-07-07"), bd.dates.back());

    // Check actual data in the BarData objoect
    EXPECT_EQ(144.880005, bd.bars["AAPL"]["open"][get_epoch_time("2017-07-03")]);
    EXPECT_EQ(242.110001, bd2.bars["SPY"]["close"][get_epoch_time("2017-07-07")]);
}