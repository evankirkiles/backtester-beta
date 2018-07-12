//
// Created by Evan Kirkiles on 7/9/18.
//

#ifndef ALGOBACKTESTER_EXECUTION_HPP
#define ALGOBACKTESTER_EXECUTION_HPP

#ifndef OrderEvent
#include "events.hpp"
#endif
#ifndef constants
#include "constants.hpp"
#endif
#ifndef ptr_vector
#include <boost/ptr_container/ptr_vector.hpp>
#endif
#ifndef DataHandler
#include "data.hpp"
#endif
#ifndef Portfolio
#include "portfolio.hpp"
#endif

// Basic execution handler to deal with Order Events
class ExecutionHandler {
public:

    // Takes in the Order Event and produces a FillEvent based on simulated slippage and commission
    void processOrder(OrderEvent event);

    // Constructor that creates the Execution Handler with the DataHandler, Portfolio, and event list references
    explicit ExecutionHandler(boost::ptr_vector<Event>& eventlist, DataHandler& datahandler, Portfolio &portfolio);

private:
    // Reference to the external event list stack and heap
    std::queue<Event>& stack_eventlist;
    std::list<Event>& heap_eventlist;
    // Reference to the external data handler
    DataHandler& datahandler;
    // Reference to the external portfolio object
    Portfolio& portfolio;
};

#endif //ALGOBACKTESTER_EXECUTION_HPP
