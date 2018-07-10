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

// Strategy header file to be included by both the main strategy and the benchmark. Strategy usage requires
// writing the strategy code into the strategy.cpp file and the benchmark code into the benchmark.cpp file.
// To save a strategy, just create a new file in the Saves folder and paste in the code from mainstrategy.cpp,
// renaming as necessary.

// Strategy base class to be inherited by all strategies.
class Strategy {
public:
    // Type specifying whether it is the algo or the bench ("ALGO" or "BENCH")
    const std::string type;
    const std::vector symbol_list = {};

protected:
    // Function that schedules other functions within the strategy
    virtual void schedule_function(void &function());
};

#endif //ALGOBACKTESTER_STRATEGY_HPP
