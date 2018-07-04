//
// Created by Evan Kirkiles on 7/4/18.
//

#ifndef ALGOBACKTESTER_DATA_HPP
#define ALGOBACKTESTER_DATA_HPP

// Data interfacer that has specialized functions for getting past N days of data
// based on which data retrieval method the user specified in their algorithm,
// as well as pushing MarketEvents onto the event stack.

#include "DataHandling/DataRetriever.hpp"

// This is the abstract base class from which both methods of data retrieval inherit from,
// simply because they both have the same functions just executed in different ways
class DataHandler {
public:

    // Virtual functions to be used by the two different methods of data storage
    // Gets the the bars of the past [days] days of the type specified for the symbols in the vector
    // Interval options are 1d (daily), 1wk (weekly), and 1mo (monthly)
    virtual std::unordered_map<std::string, std::unordered_map<long, double>> history(std::vector<std::string> symbol_list,
                                                                                      const std::string &type,
                                                                                      const std::string &interval,
                                                                                      unsigned int days) = 0;
    // Loads the next available bar of data into the latest data slot and sends a MarketEvent event
    virtual void update_bars() = 0;

    // Array holding the latest data

};

//

#endif //ALGOBACKTESTER_DATA_HPP
