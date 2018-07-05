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

    // Initialize a Data Retriever instance
    DataRetriever dr;

    // Iterate through each symbol
    for (const std::string &symbol : symbol_list) {

        // Create a brief BarData object which is decomposed into its data and its dates, the former of
        // which is put directly into fullhistory and the latter of which is sorted and then appended to fullhistory
        // Note that the startdate is not the given startdate, but the one [buffer] days earlier
        BarData info = dr.getBars(symbol, get_epoch_time(enddate),
                get_epoch_time(startdate) - buffer * 86400, interval, which);
        fullhistory.bars[symbol] = info.bars[symbol];
        appendDates(info);
    }
}

// Appends the UNIQUE dates from another BarData object into the dates of the fullhistory object.
// This is necessary because Yahoo Finance has very spotty data, so some symbols may not have data on a given day
//
// @param in             the BarData object whose dates are being appended to fullhistory
//
void StaticDataHandler::appendDates(const BarData &in) {

    // If the fullhistory's dates are empty, simply place all in
    if (fullhistory.dates.empty()) {
        fullhistory.dates = in.dates;
    } else {

        // Otherwise, use STL container sorting and other permutations to keep all unique dates
        fullhistory.dates.insert(fullhistory.dates.end(), in.dates.begin(), in.dates.end());
        std::sort(fullhistory.dates.begin(), fullhistory.dates.end());
        auto last = std::unique(fullhistory.dates.begin(), fullhistory.dates.end());
        fullhistory.dates.erase(last, fullhistory.dates.end());
    }
}