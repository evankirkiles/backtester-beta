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
class Portfolio {
public:

    // Resets the portfolio with a new initial capital amount.
    void reset_portfolio(unsigned int initial_capital);

    // Takes a market event and uses it to update the holdings for a specific stock. This will be called for every
    // stock in the portfolio (hopefully). If a stock holding does not get updated with a market event on a day where
    // another stock is updated, then the holdings are forward filled. By passing the event in as a unique pointer,
    // no other instances of this unique pointer can exist so first must be removed from the stack and then called in.
    void update_market(std::unique_ptr<Event> marketEvent);

    // Takes a fill event and uses it to update the positions and holdings for a specific stock. The fill event comes
    // from the execution handler and contains a buy or sell quantity that has already been performed.
    // Parameter is a unique poniter so do not have to make unnecessary copy and downcast when function is called.
    void update_fill(std::unique_ptr<Event> fillEvent);

    // Calculates the performance statistics for a finished backtest. Kind of inefficient and could probably be
    // improved by using internet algorithms for dynamically updating stats such as mean and variance. Oh well.
    void calculate_performance();

private:
    // Holds all the stock tickers used in the portfolio
    std::vector<std::string> symbol_list;
    // The initial capital to be used by the strategy
    unsigned int initial_capital;

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
    std::queue<std::unique_ptr<Event>>* stack_eventqueue;
    std::list<std::unique_ptr<Event>>* heap_eventlist;
};

#endif //ALGOBACKTESTER_PORTFOLIO_HPP
