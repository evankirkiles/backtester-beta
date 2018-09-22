//
// Created by Evan Kirkiles on 7/9/18.
//

#ifndef ALGOBACKTESTER_EXECUTION_HPP
#define ALGOBACKTESTER_EXECUTION_HPP

#ifndef OrderEvent
#include "events.hpp"
#endif
#ifndef constants
#include "include/constants.hpp"
#endif
#ifndef ptr_vector
#include <boost/ptr_container/ptr_vector.hpp>
#endif
#ifndef DataHandler
#include "data.hpp"
#endif
#ifndef Portfolio
#include "include/portfolio.hpp"
#endif
#ifndef queue
#include <queue>
#endif
#ifndef list
#include <list>
#endif

// Basic execution handler to deal with Signal Events and Order Events. This execution handler performs calculations
// related to slippage and risk management to simulate real trading scenarios. For example, if an
// order exceeds a set percentage of the market volume in a day, the execution handler will
// divide it up into multiple orders.
//
// @member stack_eventlist      a pointer to the containing strategy's event stack (which is actually a queue)
// @member heap_eventlist       a pointer to the containing strategy's event heap
// @member datahandler          a pointer to the data retrieval system (for use in getting market volume, other stats)
// @member portfolio            a pointer to the strategy's portfolio to keep track of the holdings
//
class ExecutionHandler {
public:
    // Constructor that creates the Execution Handler with the DataHandler, Portfolio, and event list references
    ExecutionHandler(std::queue<Event*>* stack, std::list<Event*>* heap,
                              DataHandler* datahandler, Portfolio* portfolio);

    // Takes in the Order Event and produces a FillEvent based on fill limits (may split it into multiple orders)
    void process_order(const OrderEvent &event);
    // Takes in a Signal Event and converts it into an order based on the portfolio, slippage, and commission
    void process_signal(const SignalEvent &event);

    // Calculates the IB commission on an order based on a quantity
    double calculate_commission(int quantity);
    // Calculates the slippage on an order
    double

private:
    // Pointers to the external event list stack and heap
    std::queue<Event*>* stack_eventlist;
    std::list<Event*>*heap_eventlist;
    // Pointer to the external data handler
    DataHandler* datahandler;
    // Pointer to the external portfolio object
    Portfolio* portfolio;
};

#endif //ALGOBACKTESTER_EXECUTION_HPP
