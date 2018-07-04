//
// Created by Evan Kirkiles on 7/1/18.
//

#include <gtest/gtest.h>
#include "DataHandling/DataRetriever.hpp"

// Yahoo Finance Downloader test fixture
class YahooFinanceDownloaderFixture : public ::testing::Test {
protected:
    void TearDown() override {}
    void SetUp() override {}

public:

    // Default constructor
    YahooFinanceDownloaderFixture() : Test() { }

    // Destructor
    ~YahooFinanceDownloaderFixture() override = default;
};

// Tests whether retrieves the correct crumb
// Should always pass, unless something intrinsically changes with Yahoo Finance crumb structure
TEST(YahooFinanceDownloaderFixture, correctcrumb) {

    // Instance of Yahoo Finance Downloader
    std::unique_ptr<YahooFinanceDownloader> yfd;
    yfd->downloadCSV("AAPL", 1498968000, 1499054400);

    // Should have only two lines, but if crumb is not correct then it will have more
    std::ifstream in((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());

    // If crumb was not received then first line will just be "{"
    std::string str;
    std::getline(in, str);

    EXPECT_NE("{", str);

    // Removes the files used for testing
    std::remove((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());
}

// Tests whether downloads the correct data
// Just in case Yahoo Finance ever changes their data download format
TEST(YahooFinanceDownloaderFixture, csvdownload) {

    // Instance of Yahoo Finance Downloader
    std::unique_ptr<YahooFinanceDownloader> yfd;
    yfd->downloadCSV("AAPL", 1498968000, 1499054400);

    // Should only have two lines, the column titles and a single day of data
    bool working = false;
    std::ifstream in((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());
    std::string str;
    while (std::getline(in , str)) {
        working = str.substr(0, 4) == "Date" || str.substr(0, 10) == "2017-07-03";
    }

    EXPECT_TRUE(working);

    // Removes the files used for testing
    std::remove((std::string(constants::CSV_DIR) + std::string("AAPL.csv")).c_str());
}
