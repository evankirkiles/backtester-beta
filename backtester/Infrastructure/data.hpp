//
// Created by Evan Kirkiles on 7/4/18.
//

#ifndef ALGOBACKTESTER_DATA_HPP
#define ALGOBACKTESTER_DATA_HPP

// Data interfacer that has specialized functions for getting past N days of data
// based on which data retrieval method the user specified in their algorithm

#include "DataHandling/DataRetriever.hpp"

// This is the abstract base class from which both methods of data retrieval inherit from,
// simply because they both have the same functions just executed in different ways
class DataHandler {
public:

    // Virtual functions to be used by the two different methods of data storage
    // Gets the the bars of the past [days] days of the type specified for the symbols in the vector
    // Interval options are "1d" (daily), "1wk" (weekly), and "1mo" (monthly)
    virtual BarData history(const std::vector<std::string> &symbol_list, const std::string &type,
                            const std::string &interval, unsigned int days) = 0;
};

// First class pulls all the possible required data before the algorithm begins, and then runs algo
// This vastly improves speed (only one internet request compared to many), but does not scale well,
// only really practical for EOD data with Yahoo Finance
class StaticDataHandler:DataHandler {
public:

    // Default constructor
    explicit StaticDataHandler() = default;

    // Initializer that builds the complete history of data in BarData form and puts it into the
    // fullhistory item. The parameters are self-explanatory except for the buffer, which is
    // a value that determines how much earlier data should be pulled before the startdate,
    // a value that should be defined by the algorithm's maximum history requests
    void buildHistory(const std::vector<std::string> &symbol_list, const std::string &type, const std::string &interval,
                      const std::string &startdate, const std::string &enddate, unsigned int buffer);

    // Inherited function from abstract base class DataHandler; gets data from N days back
    // This data is pulled FROM the fullhistory BarData containing all of the data
    BarData history(const std::vector<std::string> &symbol_list, const std::string &type,
                    const std::string &interval, unsigned int days) override;

private:
    // Map of all the data downloaded beforehand in the form of a BarData item
    BarData fullhistory;

    // Function that merges all unique dates of a new BarData's dates vector into fullhistory
    void appendDates(const BarData &in);
};

// Second class only pulls data when the algorithm requests it during the algo's run thread
// This is less efficient in terms of speed but far more efficient in terms of memory because it does
// not store every single bar of data--in fact, it gets data dynamically so is more similar to
// a realtime trader and is likely what will be used when the program is switched to Bloomberg API
class DynamicDataHandler:DataHandler {

    // Default constructor
    explicit DynamicDataHandler() = default;

    // Inherited function from abstract base class DataHandler; gets data from N days back.
    // This data is pulled dynamically onto the stack and deleted when the algorithm data handler
    // function leaves the scope, thus allowing for higher quantities of data to be used efficiently
    BarData history(const std::vector<std::string> &symbol_list, const std::string &type,
                    const std::string &interval, unsigned int days) override;
};


#endif //ALGOBACKTESTER_DATA_HPP
