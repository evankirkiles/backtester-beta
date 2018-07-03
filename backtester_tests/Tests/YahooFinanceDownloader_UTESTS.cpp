//
// Created by Evan Kirkiles on 7/1/18.
//

#include <gtest/gtest.h>
#include "DataHandling/DataRetriever.hpp"

// Yahoo Finance Downloader test fixture
class YahooFinanceDownloaderFixture : public ::testing::Test {
protected:
    virtual void TearDown() {}
    virtual void SetUp() {}

public:
    // Instance of Yahoo Finance Downloader
    YahooFinanceDownloader* yfd;

    // Initializes test variables to be used
    YahooFinanceDownloaderFixture() : Test() {
        yfd = new YahooFinanceDownloader();
        yfd->downloadCSV("AAPL", 1498968000, 1499054400);
    }

    // Destructor for YFD instance
    virtual ~YahooFinanceDownloaderFixture() {
        delete yfd;
    }
};

TEST(YahooFinanceDownloaderFixture, correctcrumb) {

    // Should have only two lines, but if crumb is not correct then it will have more
    bool working = false;
    std::ifstream in((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());

    // If crumb was not received then first line will just be "{"
    std::string str;
    if (std::getline(in, str)) {
        working = str != "{";
    }

    EXPECT_TRUE(working);
}

TEST(YahooFinanceDownloaderFixture, csvdownload) {

    // Should only have two lines, the column titles and a single day of data
    bool working = false;
    std::ifstream in((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());
    std::string str;
    while (std::getline(in , str)) {
        working = str.substr(0, 4) == "Date" || str.substr(0, 10) == "2017-07-03";
    }

    EXPECT_TRUE(working);
}
