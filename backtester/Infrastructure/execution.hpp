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

// Basic execution handler to deal with Order Events
class ExecutionHandler {
public:

    // Takes in the Order Event and produces a FillEvent based on simulated slippage and commission
    void processOrder(OrderEvent event);

private:
    // Reference to the external event list
    boost::ptr_vector<Event>& eventlist;
    // Reference to the external data handler
    DataHandler& datahandler;
};

#endif //ALGOBACKTESTER_EXECUTION_HPP
