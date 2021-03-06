//
// Created by Evan Kirkiles on 7/4/18.
//

#include "backtester/include/data.hpp"

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
//  ''--------->              must be greater than the maximum number of days requested by history
//
void StaticDataHandler::buildHistory(const std::vector<std::string> &symbol_list, const std::string &startdate,
                                     const std::string &enddate, const std::string &interval,
                                     const std::vector<std::string> &which, unsigned int buffer) {

    // Initialize a Data Retriever instance
    YFDDataRetriever dr;

    // Iterate through each symbol
    for (const std::string &symbol : symbol_list) {

        // Create a brief BarData object which is decomposed into its data and its dates, the former of
        // which is put directly into fullhistory and the latter of which is sorted and then appended to fullhistory
        // Note that the startdate is not the given startdate, but the one [buffer] days earlier
        BarData info = dr.getBars(symbol, get_epoch_time(startdate) - buffer * 86400,
                get_epoch_time(enddate), interval, which);
        fullhistory.bars[symbol] = info.bars[symbol];
        appendDates(info, fullhistory);
    }
}

// Retrieves the requested N days of history based on the given date in seconds since the 1970 epoch. For the
// StaticDataHandler class, this accesses the fullhistory BarData object which already has all possible data
// points that could be requested by the algorithm.
//
// This function must only be called AFTER calling buildHistory(). It may only have parameters that match
// values passed in to buildHistory(). Most importantly, days must be less than the initial buffer on the
// builHistory() function.
//
// @param currentTime     the date, in seconds since 1970 epoch, from which the data is being requested
// @param symbol_list     the tickers of the symbols for which to retrieve the history
// @param type            "open", "close", "high", "low", "adj", "volume"
// @param interval        "1d" for daily, "1wk" for weekly, "1mo" for monthly
// @param days            the number of days back from the currentTime for which to fetch the data
// @return                a BarData object containing the bars of the given type for the symbols requested
//
BarData StaticDataHandler::history(unsigned long currentTime, const std::vector<std::string> &symbol_list,
                                   const std::vector<std::string> &which, const std::string &interval, unsigned int days) {

    // Placeholder BarData that is returned
    BarData bd;

    // Accesses the dates vector and finds the index of the date closest to the current date (below it)
    // Does this by finding the first value in the vector that is >= than the currentTime, and then
    // iterating back 1 to get an iterator for the most recent bar's date.
    auto closest = std::lower_bound(fullhistory.dates.begin(), fullhistory.dates.end(), currentTime);
    --closest;

    // Then get all the dates necessary and get their data from fullhistory, placing it into BarData
    unsigned long stopDate = currentTime - days * 86400;
    while (*closest >= stopDate){
        // Put the dates into the dates vector
        bd.dates.emplace_back(*closest);

        // Iterate through the symbols
        for (const std::string &symbol : symbol_list) {
            // Iterate through the requested bars
            for (const std::string &type : which) {

                // Append the data to the returned BarData
                bd.bars[symbol][type][*closest] = fullhistory.bars[symbol][type][*closest];
            }
        }
        --closest;
    }

    // Reverse the dates to put them in order
    std::reverse(bd.dates.begin(), bd.dates.end());

    // Now return the bardata
    return bd;
}

// Appends the UNIQUE dates from another BarData object into the dates of the target Bardata object.
// This is necessary because Yahoo Finance has very spotty data, so some symbols may not have data on a given day.
// Also allows indexing through all market days rather than every calendar day.
//
// @param in              the BarData object whose dates are being appended to fullhistory
//
void appendDates(const BarData &in, BarData &target) {

    // If the target's dates are empty, simply place all in
    if (target.dates.empty()) {
        target.dates = in.dates;
    } else {
        // Otherwise, use STL container sorting and other permutations to keep all unique dates
        target.dates.insert(target.dates.end(), in.dates.begin(), in.dates.end());
        std::sort(target.dates.begin(), target.dates.end());
        auto last = std::unique(target.dates.begin(), target.dates.end());
        target.dates.erase(last, target.dates.end());
    }
}


// Dynamic Data Handler which uses data requests sent by the algorithm to dynamically download data which is
// used and then deleted. More efficient in terms of memory and should be used when testing higher frequency
// strategies rather than simple daily-run algos.
//
// @param currentTime     the date, in seconds since 1970 epoch, from which the data is being requested
// @param symbol_list     the tickers of the symbols for which to retrieve the history
// @param type            "open", "close", "high", "low", "adj", "volume"
// @param interval        "1d" for daily, "1wk" for weekly, "1mo" for monthly
// @param days            the number of days back from the currentTime for which to fetch the data
// @return                a BarData object containing the bars of the given type for the symbols requested
//
static BarData DynamicDataHandler::history(unsigned long currenttime, const std::vector<std::string> &symbol_list,
                                    const std::vector<std::string> &which, const std::string &interval,
                                    unsigned int days) {

    // YFDDataRetriever instance
    YFDDataRetriever dr;
    // BarData object to return and placeholder BarData
    BarData bd;
    BarData placeholder;

    // Cycle through all requested symbols and append each to the BarData object
    for (const std::string &symbol : symbol_list) {

        // Going back N days is simply going back N*86400 seconds, so that will be the startdate
        placeholder = dr.getBars(symbol, (currenttime - days * 86400), currenttime, interval, which);
        bd.bars[symbol] = placeholder.bars[symbol];
        appendDates(placeholder, bd);
    }

    // Return
    return bd;
}