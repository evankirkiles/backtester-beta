//
// Created by Evan Kirkiles on 7/10/18.
//

#ifndef ALGOBACKTESTER_PORTFOLIO_HPP
#define ALGOBACKTESTER_PORTFOLIO_HPP

// Standard library includes
#ifndef map
#include <map>
#endif
#ifndef unordered_map
#include <unordered_map>
#endif
#ifndef string
#include <string>
#endif
#ifndef queue
#include <queue>
#endif
#ifndef list
#include <list>
#endif

// Include custom classes
#include "events.hpp"

// Portfolio class which handles holdings calculations and storing holdings-related information. Reacts only to MARKET
// events and FILL events as these are the only events which affect the holdings.
//
// @member symbol_list           the symbols traded by the algorithm, localized for iterative purposes
// @member initial_capital       the initial capital to be traded
// @member all_positions         map of the quantity held in each stock at every date
// @member current_positions     map of the quantity held in each stock currently
// @member all_holdings          map of the value of the positions in each stock at every date (includes commission)
// @member current_holdings      map of the value of the positions currently (includes commission tracker)
// @member performance_map       contains all the performance statistics calculated at end of backtest
// @member stack_eventqueue      reference to parent event stack
// @member heap_eventlist        reference to parent event heap
//
class Portfolio {
public:
    // Initializes the portfolio given the symbols, initial capital, and references to the STACK and HEAP
    explicit Portfolio(std::vector<std::string> symbol_list, unsigned int initial_capital, unsigned long start_date,
                       std::queue<Event*>* stack_eventqueue, std::list<Event*>* heap_eventlist);

    // Resets the portfolio with a new initial capital amount.
    void reset_portfolio(unsigned int initial_capital, unsigned long start_date);

    // Takes a market event and uses it to update the holdings for a specific stock. This will be called for every
    // stock in the portfolio (hopefully). If a stock holding does not get updated with a market event on a time where
    // another stock is updated, then the holdings are forward filled.
    void update_market(Event* marketEvent);

    // Takes a fill event and uses it to update the positions and holdings for a specific stock. The fill event comes
    // from the execution handler and contains a buy or sell quantity that has already been performed.
    void update_fill(Event* fillEvent);

    // Calculates the performance statistics for a finished backtest. Kind of inefficient and could probably be
    // improved by using internet algorithms for dynamically updating stats such as mean and variance. Oh well.
    void calculate_performance();

private:
    // Holds all the stock tickers used in the portfolio
    std::vector<std::string> symbol_list;
    // The initial capital to be used by the strategy
    unsigned int initial_capital;
    // The start date of the strategy, only used for initializing the positions maps
    unsigned long start_date;

    // The maps of positions at their respective unix timestamps (quantitites of each stock)
    std::map<long, std::unordered_map<std::string, double>> all_positions;
    std::unordered_map<std::string, double> current_positions;
    // The maps of holdings at their respective unix timestamps, also records commissions (quantity * price of each stock)
    std::map<long, std::unordered_map<std::string, double>> all_holdings;
    std::unordered_map<std::string, double> current_holdings;

    // Performance map holding the evaluation statistics calculated at the end of a backtest, including:
    //  --> alpha, beta, sharpe ratio, sortino ratio, high water mark, max drawdown
    std::unordered_map<std::string, double> performance_map;

    // Local pointers to the event stack and heap
    std::queue<Event*>* const stack_eventqueue;
    std::list<Event*>* const heap_eventlist;
};

#endif //ALGOBACKTESTER_PORTFOLIO_HPP
