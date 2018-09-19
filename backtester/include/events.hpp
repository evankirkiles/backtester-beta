//
// Created by Evan Kirkiles on 7/6/18.
//

#ifndef ALGOBACKTESTER_EVENTS_HPP
#define ALGOBACKTESTER_EVENTS_HPP

// Standard library includes
#ifndef string
#include <string>
#endif
#ifndef unordered_map
#include <unordered_map>
#endif
#ifndef vector
#include <vector>
#endif

// Custom library includes
#include "strategy.hpp"

// Base Event structure to which I can add features. All Events must inherit three member variables:
//
// @member datetime       the simulated time at which the event occurred
// @member type           "SCHEDULED", "SIGNAL", "ORDER", or "FILL" for the type of the Event
//  ''---------->             the STACK's events are processed immediately, while the HEAP's are not
//
struct Event {
    const std::string type;
    const unsigned long datetime = 0;

    // Default destructor to allow for polymorphism
    virtual ~Event() = default;
};

// Scheduled Event that is placed onto the heap depending on when the algorithm has scheduled it to run. This
// is the module that allows for functions to be run at certain times during the calendar. Rather than have a running
// clock which determines the time the function runs, the functions are simply placed in order on the heap.
//
// @member function       the function to be run, must always be void (return type would be useless anyways)
// @member stratInstance  the strategy object that owns the member function which will be run
//
struct ScheduledEvent: public Event {
    void (*function);
    Strategy& stratInstance;

    // Constructor for the ScheduledEvent
    ScheduledEvent(void (*function), Strategy& strat, unsigned long when);
};

// Market Event that is produced by the DataHandler when the strategy is initialized. These are added onto
// the event heap with set dates, so the portfolio can cycle through the market information and update the
// holdings on a specified frequency. Scheduled events will be scattered between.
//
// @member symbols         a vector of the symbols being updated on the given date
// @member data            an unordered map of the closes on the given interval wrt their symbol
//
struct MarketEvent: public Event {
    std::vector<std::string> symbols;
    const std::unordered_map<std::string, double> data;

    // Constructor for the MarketEvent
    MarketEvent(const std::vector<std::string>& symbols, const std::unordered_map<std::string, double>& data,
                unsigned long datetime);
};

// Signal Event that is produced when the algorithm performs an order. This acts as a middleman between
// the algorithm and any order events because some orders may be too large to fill in a single day and so
// must be spread out into multiple orders. The signal will always be on the stack event list.
//
// @member symbol         the symbol for which the signal is being sent
// @member percentage     the target percent of the request (positive for long, negative for short)
//
struct SignalEvent: public Event {
    const std::string symbol;
    const double percentage;

    // Constructor for the SignalEvent
    SignalEvent(std::string symbol, double percentage, unsigned long datetime);
};

// Order Event that is produced when a signal from the algorithm is received. It is handled by the
// execution handler which may split the order into multiples if the full order cannot be filled in
// a single bar, as well as calculate any necessary risk management options. Order events can be placed
// on both the STACK and the HEAP, where the STACK will perform them as soon as possible before any HEAP fill.
//
// @member symbol         the symbol for which the signal is being sent
// @member quantity       the number of shares being bought (not const because needs to be mutable by execution)
//
struct OrderEvent: public Event {
    const std::string symbol;
    int quantity;

    // Constructor for the OrderEvent
    OrderEvent(std::string symbol, int quantity, unsigned long datetime);
};

// Fill event which is produced when an order from the algorithm is filled. All slippage and risk
// management will have been handled by the execution handler, so this event simply contains the cost
// and the quantity filled of the order.
//
// @member symbol         the symbol for which the signal is being sent
// @member quantity       the number of shares filled (positive for bought, negative for sold)
// @member cost           the price of the fill not including slippage or commission
// @member slippage       the cost of the slippage due to variations in bid/ask spread (simulated)
// @member commission     the cost of commission given by the simulated broker (Interactive Brokers)
//
struct FillEvent: public Event {
    const std::string symbol;
    const int quantity;
    const double cost, slippage, commission;

    // Constructor for the FillEvent
    FillEvent(std::string symbol, int quantity, double cost, double slippage, double commission,
              unsigned long datetime);
};

// Unary function for searching the eventlist that helps to return the first date greater than the specified
// value. This can be used for insertion, as you can put in an item immediately before this element
// which mimics scheduling it at the date given.
struct date_compare {
    explicit date_compare(const unsigned long p_date) : date(p_date) {}
    const unsigned long date;
    inline bool operator()(const std::unique_ptr<Event> &data) {
        // Returns true for the first element whose date is later than the given date
        return (data->datetime > date);
    }
};


#endif //ALGOBACKTESTER_EVENTS_HPP
