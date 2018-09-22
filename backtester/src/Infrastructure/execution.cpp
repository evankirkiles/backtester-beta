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
void ExecutionHandler::process_order(const OrderEvent &event) {

    // Retrieve the most recent cost of the desired stock
    BarData priceInfo = datahandler->history(event.datetime,
            {event.symbol}, {hist_data_types_YFD::CLOSE, hist_data_types_YFD::VOLUME}, "1d", 1);

    // First, check if it is necessary to split the order into multiple orders. This is done by
    // setting a threshold percentage of the most recent day's volume and, if the order goes over said
    // threshold, put whatever could not be ordered today into an order for the next day.
    // CURRENT THRESHOLD: 2.5%
    int quantity = event.quantity;
    if (abs(quantity) > priceInfo.bars[event.symbol][hist_data_types_YFD::VOLUME][priceInfo.dates.back()] *
                              order_constants::MKTVOL_THRESHOLD) {

        // Cap the quantity at the volume limit
        quantity = ((event.quantity > 0 ) - (event.quantity < 0)) *
                (int)priceInfo.bars[event.symbol][hist_data_types_YFD::VOLUME][priceInfo.dates.back()];

        // Log the failure to fill complete order
        std::cout << "Could not fill all " << event.quantity << " shares of " << event.symbol << ", only got " << quantity << ".";

        // Make a new OrderEvent for after the next market event date with the rest of the volume.
        auto iter = std::find_if(heap_eventlist->begin(), heap_eventlist->end(), mkt_date_compare(event.datetime + 1));
        heap_eventlist->insert(iter++, new OrderEvent(event.symbol,
                                                    (int)priceInfo.bars[event.symbol][hist_data_types_YFD::VOLUME][priceInfo.dates.back()] - quantity,
                                                    event.datetime + 86400));
    }

    // Calculate the cost of the order now with the most recent price
    double cost = priceInfo.bars[event.symbol][hist_data_types_YFD::CLOSE][priceInfo.dates.back()] * quantity;

    // Now write the quantity and order information into a new fill event which is put onto the stack
//    stack_eventlist->emplace(new FillEvent, event.symbol, quantity, cost, );


    // 5 bps of slippage on each order to simulate buy-ask spread (naive approach)


}

// Calculates the commission for a quantity of stock, currently using Interactive Broker's prices.
double ExecutionHandler::calculate_commission(int quantity) {
    // Minimum cost is $1.30 on Interactive Brokers, but this logic is very flawed
    return (quantity <= 500) ? std::max(1.3, 0.013 * quantity) : std::max(1.3, 0.008*quantity);
}

// Constructor for the Execution Handler that creates the references to the global eventlist
// and the DataHandler being used by the algorithm
//
// @param eventlist     A reference to the global event list
// @param datahandler   A reference to the algorithm's datahandler
//
ExecutionHandler::ExecutionHandler(std::queue<Event*>* p_stack,
                                   std::list<Event*>* p_heap,
                                   DataHandler* p_datahandler,
                                    Portfolio* p_portfolio) : stack_eventlist(p_stack),
                                                              heap_eventlist(p_heap),
                                                              datahandler(p_datahandler),
                                                              portfolio(p_portfolio) {}
