//
// Created by Evan Kirkiles on 7/9/18.
//

#include "backtester/include/execution.hpp"

// Execution handler which simulates slippage, commission, and risk management

// Function that uses an OrderEvent and produces a FillEvent. In between it calculates slippage,
// commissions, and necessary risk management to produce a fill event. For example, if an order
// is too large, then the order may be split into multiple scheduled order events across the next
// few bars of data.
//
// @param event         The OrderEvent to be processed
//
void ExecutionHandler::processOrder(const OrderEvent& event) {

    // Retrieve the most recent cost of the desired stock
    BarData priceInfo = datahandler.history(event.datetime, {event.symbol}, {"close", "volume"}, "1d", 1);

    // First, check if it is necessary to split the order into multiple orders. This is done by
    // setting a threshold percentage of the most recent day's volume and, if the order goes over said
    // threshold, put whatever could not be ordered today into an order for the next day.
    // CURRENT THRESHOLD: 2.5%
    if (abs(event.quantity) > priceInfo.bars[event.symbol]["volume"][priceInfo.dates.back()] *
                              order_constants::MKTVOL_THRESHOLD) {

        // Cap the quantity at the volume limit
        auto newquantity = static_cast<int>(((event.quantity > 0 ) - (event.quantity < 0)) *
                                            priceInfo.bars[event.symbol]["volume"][priceInfo.dates.back()]);

        // Make a new OrderEvent for the next latest date (currently functions by adding a day to the event's date
        // and using the custom unary function to find the iterator at the most recent date after.
        auto iter = std::find_if(heap_eventlist.begin(), heap_eventlist.end(), date_compare(event.datetime + 86400));
        heap_eventlist.insert(iter, std::make_unique<OrderEvent>(event.symbol,
                                                           priceInfo.bars[event.symbol]["volume"][priceInfo.dates.back()] - event.quantity,
                                                           event.datetime + 86400));

        // TODO: Write the filling mechanism for slippage and risk management


        // Determine how many shares would be

    } else {

        // TODO: Write the filling mechanism for slippage and risk management

    }


    // 5 bps of slippage on each order to simulate buy-ask spread (naive approach)


}

// Constructor for the Execution Handler that creates the references to the global eventlist
// and the DataHandler being used by the algorithm
//
// @param eventlist     A reference to the global event list
// @param datahandler   A reference to the algorithm's datahandler
//
ExecutionHandler::ExecutionHandler(std::queue<std::unique_ptr<Event>> &p_stack,
                                   std::list<std::unique_ptr<Event>> &p_heap,
                                   DataHandler &p_datahandler,
                                    Portfolio &p_portfolio) : stack_eventlist(p_stack),
                                                              heap_eventlist(p_heap),
                                                              datahandler(p_datahandler),
                                                              portfolio(p_portfolio) {}