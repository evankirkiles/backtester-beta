//
// Created by Evan Kirkiles on 7/1/18.
//

#include <gtest/gtest.h>
#include "DataHandling/DataRetriever.hpp"

TEST(YahooFinanceDownloader_tests, csvdownload) {

    // Create an instance of YFD and download a single day of CSV data
    YahooFinanceDownloader yfd;
    yfd.downloadCSV("AAPL", 1498968000, 1499054400);

    // Should only have two lines, the column titles and a single day of data
    bool working = false;
    std::ifstream in("./backtester/DataHandling/CSV/AAPL.csv");
    std::string str;
    while (std::getline(in , str)) {
        working = str.substr(0, 4) == "Date" || str.substr(0, 10) == "2017-07-03";
    }

    EXPECT_TRUE(working);
}
