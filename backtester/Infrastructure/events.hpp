//
// Created by Evan Kirkiles on 7/6/18.
//

#ifndef ALGOBACKTESTER_EVENTS_HPP
#define ALGOBACKTESTER_EVENTS_HPP

#ifndef string
#include <string>
#endif
#ifndef Strategy
#include "Strategies/strategy.hpp"
#endif

// Base Event structure to which I can add features. All Events must inherit three member variables:
//
// @member datetime       the simulated time at which the event occurred
// @member type           "SCHEDULED", "SIGNAL", "ORDER", or "FILL" for the type of the Event
// @member target         "ALGO" or "BENCH" signifying which algorithm the event is for
// @member location       "STACK" or "HEAP", specifying when the events should be processed
//  ''---------->             the STACK's events are processed immediately, while the HEAP's are not
//
struct Event {
    const std::string type, target, location;
    const unsigned long datetime;

    // Default destructor to allow for polymorphism
    virtual ~Event() = default;
};

// Scheduled Event that is placed onto the heap depending on when the algorithm has scheduled it to run. This
// is the module that allows for functions to be run at certain times during the calendar. Rather than have a running
// clock which determines the time the function runs, the functions are simply placed in order on the heap.
//
// @member strategy       a reference to the strategy class instance for which the function will be run
// @member function       the function to be run, must always be void (return type would be useless anyways)
//
struct ScheduledEvent: public Event {
    Strategy& strat;
    void (Strategy::*function);

    // Constructor for the ScheduledEvent
    ScheduledEvent(Strategy &strategy, void (Strategy::*function), unsigned long when);

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
    SignalEvent(const std::string& symbol, double percentage, unsigned long datetime,
                const std::string &target);
};

// Order Event that is produced when a signal from the algorithm is received. It is handled by the
// execution handler which may split the order into multiples if the full order cannot be filled in
// a single bar, as well as calculate any necessary risk management options.
//
// @member symbol         the symbol for which the signal is being sent
// @member percentage     the percent of holdings requested for the symbol (positive for long, negative for short)
//
struct OrderEvent: public Event {
    const std::string symbol;
    const double percentage;

    // Constructor for the OrderEvent
    OrderEvent(const std::string& symbol, double percentage, unsigned long datetime,
               const std::string &target, const std::string &location);
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
    FillEvent(const std::string& symbol, int quantity, double cost, double slippage, double commission,
              unsigned long datetime, const std::string &target, const std::string &location);
};

#endif //ALGOBACKTESTER_EVENTS_HPP