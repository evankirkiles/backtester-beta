//
// Created by Evan Kirkiles on 7/3/18.
//

#include <gtest/gtest.h>
#include "DataHandling/DataRetriever.hpp"

// Data Retriever test fixture
class DataRetrieverFixture : public ::testing::Test {
protected:
    void TearDown() override {}
    void SetUp() override {}

public:

    // Initializes test variables to be used
    DataRetrieverFixture() : Test() {}

    // Destructor
    ~DataRetrieverFixture() override = default;
};

// Tests whether the Data Retriever pulls the dates from the .csv correctly
// Should always pass, unless data from Yahoo Finance changes
TEST(DataRetrieverFixture, datepulling) {

    // Instance of Data Retriever
    std::unique_ptr<DataRetriever> dr(new DataRetriever());
    BarData bardata = dr->getBars("AAPL", "2017-07-03", "2017-07-10", "1d", "close");

    // The dates vector should have 5 dates, like so:
    std::vector<unsigned long> target = {get_epoch_time("2017-07-03"), get_epoch_time("2017-07-05"),
                                         get_epoch_time("2017-07-06"), get_epoch_time("2017-07-07"),
                                         get_epoch_time("2017-07-10")};

    EXPECT_EQ(target, bardata.dates);
}

// Tests whether get_epoch_time works correctly
TEST(DataRetrieverFixture, epochtime) {
    // Uses July 3, 2017 as an example
    EXPECT_EQ(1499054400, get_epoch_time("2017-07-03"));
}

// Tests whether get_std_time works correctly
TEST(DataRetrieverFixture, stdtime) {
    // Uses July 3, 2017 as an example
    EXPECT_EQ("2017-07-03", get_std_time(1499054400));
}