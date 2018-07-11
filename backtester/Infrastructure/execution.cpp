//
// Created by Evan Kirkiles on 7/9/18.
//

#include "execution.hpp"

// Execution handler which simulates slippage, commission, and risk management

// Function that uses an OrderEvent and produces a FillEvent. In between it calculates slippage,
// commissions, and necessary risk management to produce a fill event. For example, if an order
// is too large, then the order may be split into multiple scheduled order events across the next
// few bars of data.
//
// @param event         The OrderEvent to be processed
//
void ExecutionHandler::processOrder(OrderEvent event) {

    // Retrieve the most recent cost of the desired stock
    BarData priceInfo = datahandler.history(event.datetime, {event.symbol}, {"close", "volume"}, "1d", 1);

    // First, check if it is necessary to split the order into multiple orders. This is done by
    // setting a threshold percentage of the most recent day's volume and, if the order goes over said
    // threshold, put whatever could not be ordered today into an order for the next day.
    // CURRENT THRESHOLD: 2.5%



    // 5 bps of slippage on each order to simulate buy-ask spread (naive approach)


}

// Constructor for the Execution Handler that creates the references to the global eventlist
// and the DataHandler being used by the algorithm
//
// @param eventlist     A reference to the global event list
// @param datahandler   A reference to the algorithm's datahandler
//
ExecutionHandler::ExecutionHandler(boost::ptr_vector<Event> &p_eventlist,
                                   DataHandler &p_datahandler,
                                    Portfolio &p_portfolio) : eventlist(p_eventlist),
                                                              datahandler(p_datahandler),
                                                              portfolio(p_portfolio) {}
