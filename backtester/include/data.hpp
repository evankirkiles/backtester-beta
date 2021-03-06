//
// Created by Evan Kirkiles on 7/4/18.
//

#ifndef ALGOBACKTESTER_DATA_HPP
#define ALGOBACKTESTER_DATA_HPP

// Data interfacer that has specialized functions for getting past N days of data
// based on which data retrieval method the user specified in their algorithm

#include "YFDDataRetriever.hpp"
#include <gtest/gtest_prod.h>

// This is the abstract base class from which both methods of data retrieval inherit from,
// simply because they both have the same functions just executed in different ways
class DataHandler {
public:

    // Virtual functions to be used by the two different methods of data storage
    // Gets the the bars of the past [days] days of the type specified for the symbols in the vector
    // Interval options are "1d" (daily), "1wk" (weekly), and "1mo" (monthly)
    virtual BarData history(unsigned long currenttime, const std::vector<std::string> &symbol_list,
                            const std::vector<std::string> &which, const std::string &interval, unsigned int days) = 0;
};

// First class pulls all the possible required data before the algorithm begins, and then runs algo
// This should improve speed (only one internet request compared to many), but does not scale well,
// only really practical for EOD data with Yahoo Finance. The frequency of the market events and history
// function calls must be the same, so if a history function call wants minute-frequency data then the fullhistory
// must contain minute-level data for the entire backtest, which is incredibly inefficient. This data handler
// probably should not be used outside of EOD data because of its drawbacks.
class StaticDataHandler:DataHandler {
public:

    // Default constructor
    StaticDataHandler() = default;

    // Initializer that builds the complete history of data in BarData form and puts it into the
    // fullhistory item. The parameters are self-explanatory except for the buffer, which is
    // a value that determines how much earlier data should be pulled before the startdate
    // and should be defined by the algorithm's maximum history requests
    void buildHistory(const std::vector<std::string> &symbol_list, const std::string &startdate,
                      const std::string &enddate, const std::string &interval, const std::vector<std::string> &which,
                      unsigned int buffer);

    // Inherited function from abstract base class DataHandler; gets data from N days back
    // This data is pulled FROM the fullhistory BarData containing all of the data
    BarData history(unsigned long currenttime, const std::vector<std::string> &symbol_list,
                    const std::vector<std::string> &which, const std::string &interval, unsigned int days) override;

private:
    // Map of all the data downloaded beforehand in the form of a BarData item
    BarData fullhistory;

    // Unit test related private friend members
    FRIEND_TEST(DataHandlerFixture, static_buildshistory);
    FRIEND_TEST(DataHandlerFixture, static_historyfunction);
};

// Second class only pulls data when the algorithm requests it during the algo's run thread
// This is less efficient in terms of speed but far more efficient in terms of memory because it does
// not store every single bar of data--in fact, it gets data dynamically so is more similar to
// a realtime trader and is likely what will be used when the program is switched to Bloomberg API.
//
// The market events list initialized will first be loaded in from a history call with daily frequency
// for performance reporting. Then, later history calls are free to request whatever frequency they want
// from the online data provider.
class DynamicDataHandler:DataHandler {

    // Inherited function from abstract base class DataHandler; gets data from N days back.
    // This data is pulled dynamically onto the stack and deleted when the algorithm data handler
    // function leaves the scope, thus allowing for higher quantities of data to be used efficiently
    static BarData history(unsigned long currentTime, const std::vector<std::string> &symbol_list,
                    const std::vector<std::string> &which, const std::string &interval, unsigned int days) override;
};

// Function that merges all unique dates of a new BarData's dates vector into fullhistory
void appendDates(const BarData &in, BarData &target);

#endif //ALGOBACKTESTER_DATA_HPP
