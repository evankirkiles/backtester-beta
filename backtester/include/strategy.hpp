//
// Created by Evan Kirkiles on 7/7/18.
//

#ifndef ALGOBACKTESTER_STRATEGY_HPP
#define ALGOBACKTESTER_STRATEGY_HPP

#ifndef string
#include <string>
#endif
#ifndef queue
#include <queue>
#endif
#ifndef vector
#include <vector>
#endif
#ifndef list
#include <list>
#endif
#ifndef Portfolio
#include "portfolio.hpp"
#endif
#ifndef DataHandler
#include "data.hpp"
#endif
#ifndef ExecutionHandler
#include "execution.hpp"
#endif

// Strategy header file to be included by both the main strategy and the benchmark. Strategy usage requires
// writing the strategy code into the strategy.cpp file and the benchmark code into the benchmark.cpp file.
// To save a strategy, just create a new file in the Saves folder and paste in the code from mainstrategy.cpp,
// renaming as necessary.

// Strategy base class to be inherited by the strategy class just to allow for cleaner implementation for user.
//
// When the algorithm is run, each strategy should be run in a different thread. This allows several
// algorithms to be run rather than just a main strategy and a benchmark. Thus, each algo will have its own
// event list and will be completely self-contained. Graphics will require some form of lock or mutex if I
// want to run it in realtime with the algo, but this will probably not be the case as it is so much slower
// running in realtime compared to running after the algo has finished simulating.
//
// Before running, need to fill the heap event list with market events at a set frequency. Probably good enough to
// do each day, as the market events will only be called for performance reporting. Then, the scheduled function
// events are loaded in between the market events to simulate scheduling.
//
// @member symbol_list         list of the symbols being traded by the algorithm
// @member portfolio           object containing holdings, positions, and performance information
// @member stack_eventqueue    the actual instance of the event stack referenced by members
// @member heap_eventlist      the actual instance of the event heap referenced by members
// @member dataHandler         used for getting data within the algorithm
// @member executionHandler    performs risk management and slippage calculations on orders, producing fill events
//
class BaseStrategy {
public:
    // Property related variables
    // List of the symbols being used in the algorithm
    const std::vector<std::string> symbol_list;

    // Public portfolio so it can be accessed by graphing components
    Portfolio portfolio;

    // Runs the strategy itself, should be called on a new thread
    virtual void run();

protected:
    // Start and end dates, in unix timestamp time
    const unsigned long start_date, end_date;

    // Function that schedules other functions within the strategy
    void schedule_function(void (*func));

    // The strategy-unique event list
    // Events on this queue will always be performed over events on the heap list
    std::queue<Event*> stack_eventqueue;
    // Events on this list will be run in order, is initially populated by MarketEvents when strategy is initialized
    std::list<Event*> heap_eventlist;

    // Instances of necessary algorithmic components
    DataHandler dataHandler;
    ExecutionHandler executionHandler;
};

// The actual strategy class which contains the logic for the strategy. It inherits from BaseStrategy so that
// the user does not have access to the complete back end code behind the functioning and so cannot mess anything
// up. The only things that can be changed are fully changeable.
class Strategy : public BaseStrategy {
public:
    // Constructs an instance of the strategy for the given user-changeable parameters
    Strategy(unsigned int initial_capital, unsigned long start_date, unsigned long end_date);

    // Runs the strategy
    void run();
};

#endif //ALGOBACKTESTER_STRATEGY_HPP
