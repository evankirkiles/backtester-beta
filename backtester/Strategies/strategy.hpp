//
// Created by Evan Kirkiles on 7/7/18.
//

#ifndef ALGOBACKTESTER_STRATEGY_HPP
#define ALGOBACKTESTER_STRATEGY_HPP

#ifndef string
#include <string>
#endif
#ifndef vector
#include <vector>
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
class Strategy {
public:
    // Type specifying whether it is the algo or the bench ("ALGO" or "BENCH")
    const std::string type;
    const std::vector symbol_list;

    // Public portfolio so it can be accessed by graphing components
    Portfolio portfolio;

protected:
    // Function that schedules other functions within the strategy
    virtual void schedule_function(void &function());

    // Instances of necessary algorithmic components
    DataHandler dataHandler;
};

#endif //ALGOBACKTESTER_STRATEGY_HPP
