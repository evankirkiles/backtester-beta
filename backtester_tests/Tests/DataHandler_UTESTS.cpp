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