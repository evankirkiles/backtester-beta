//
// Created by Evan Kirkiles on 6/30/18.
//

#ifndef ALGOBACKTESTERV2_DATARETRIEVER_HPP
#define ALGOBACKTESTERV2_DATARETRIEVER_HPP

// Include for string stream
#ifndef stringstream
#include <sstream>
#endif

#include "YahooFinanceDownloader.hpp"

// Packet of data sent by the CSV Reader
struct BarData {
    // Holds the symbol bar-requested data for each date
    // Format: bars[date]
    std::unordered_map<std::string, std::unordered_map<unsigned long, double>> bars;
    // Vector holding all the dates, SORTED earliest to latest from beginning to end
    std::vector<unsigned long> dates;
};

// Reads the data into BarData format from the csv
class DataRetriever {
public:

    // Basic default constructor
    explicit DataRetriever() = default;
    // Downloads the .csv and returns its data in BarData format (FOR THE FIELD YOU REQUEST)
    BarData getBars(const std::string &symbol, const unsigned long &startdate, const unsigned long &enddate,
                    const std::string &interval, const std::string &which);

};

// Global functions for converting epoch date to readable string and back
unsigned long get_epoch_time(const std::string &date);
std::string get_std_time(unsigned long epochtime);

#endif //ALGOBACKTESTERV2_DATARETRIEVER_HPP
