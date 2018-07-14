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
#include "../Infrastructure/portfolio.hpp"
#endif
#ifndef DataHandler
#include "../Infrastructure/data.hpp"
#endif
#ifndef ExecutionHandler
#include "../Infrastructure/execution.hpp"
#endif

// Strategy header file to be included by both the main strategy and the benchmark. Strategy usage requires
// writing the strategy code into the strategy.cpp file and the benchmark code into the benchmark.cpp file.
// To save a strategy, just create a new file in the Saves folder and paste in the code from mainstrategy.cpp,
// renaming as necessary.

// Strategy base class to be inherited by all strategies.
//
// When the algorithm will be run, each strategy should be run in a different thread. This allows several
// algorithms to be run rather than just a main strategy and a benchmark. Thus, each algo will have its own
// event list and will be completely self-contained. Graphics will require some form of lock or mutex if I
// want to run it in realtime with the algo, but this will probably not be the case as it is so much slower
// running in realtime compared to running after the algo has finished simulating.
//
class Strategy {
public:
    // Property related variables
    // List of the symbols being used in the algorithm
    const std::vector<std::string> symbol_list;

    // Public portfolio so it can be accessed by graphing components
    Portfolio portfolio;

protected:
    // Function that schedules other functions within the strategy
    virtual void schedule_function(void (*func));

    // The strategy-unique event list
    // Events on this queue will always be performed over events on the heap list
    std::queue<std::unique_ptr<Event>> stack_eventqueue;
    // Events on this list will be run in order, is initially populated by MarketEvents when strategy is initialized
    std::list<std::unique_ptr<Event>> heap_eventlist;

    // Instances of necessary algorithmic components
    DataHandler dataHandler;
    ExecutionHandler executionHandler;
};

#endif //ALGOBACKTESTER_STRATEGY_HPP
