//
// Created by Evan Kirkiles on 7/4/18.
//

#include "data.hpp"

// Static Data Handler which downloads all the possible required data before algorithm is run to reduce
// internet requests which take a significant amount of time. Does not scale well in terms of memory so
// use this with backtests with a reasonable amount of bars (any daily frequency are fine).
//
// This function MUST be called before calling history().
//
// @param symbol_list    the list of symbols for which to download data
// @param startdate      the start date for the backtest
// @param enddate        the end date for the backtest
// @param interval       "1d" for daily, "1wk" for weekly, "1mo" for monthly (Yahoo Finance specific)
// @param which          "open", "low", 'high", "close", "adj", "volume"
// @param buffer         the wiggle room amount of data to add before the startdate (defined in algo)
//
void StaticDataHandler::buildHistory(const std::vector<std::string> &symbol_list, const std::string &startdate,
                                     const std::string &enddate, const std::string &interval,
                                     const std::string &which, unsigned int buffer) {

    

}