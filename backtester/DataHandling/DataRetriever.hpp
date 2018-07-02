//
// Created by Evan Kirkiles on 6/30/18.
//

#ifndef ALGOBACKTESTERV2_DATARETRIEVER_HPP
#define ALGOBACKTESTERV2_DATARETRIEVER_HPP

#include "YahooFinanceDownloader.hpp"

// Packet of data sent by the CSV Reader
struct BarData {

    // Holds the symbol data for each date
    // Format: bars[symbol][date][open / high / low / close / volume / adj]
    std::unordered_map<std::string, std::unordered_map<long, std::unordered_map<std::string, double>>> bars;
    // Vector holding all the dates, SORTED earliest to latest from beginning to end
    std::vector<long> allDates;
    // Holds the current date index for iterating through the bardata
    unsigned int currentDatesIndex;

};

// Reads the data into BarData format from the csv
class DataRetriever {
public:

    // Basic default constructor
    explicit DataRetriever() = default;
    // Downloads the .csv and returns its data in BarData format
    BarData getBars(const std::string &symbol, const std::string &startdate, const std::string &enddate);

};

// Global functions for converting epoch date to readable string and back
unsigned long get_epoch_time(const std::string &date);
std::string get_std_time(unsigned long epochtime);

#endif //ALGOBACKTESTERV2_DATARETRIEVER_HPP
