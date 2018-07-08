//
// Created by Evan Kirkiles on 7/6/18.
//

#include "events.hpp"

// Initializer lists for the construction of each Event Type

// Scheduled Event initializer list
// Signal Event initializer list
SignalEvent::SignalEvent(const std::string &p_symbol, const double p_percentage, const unsigned long p_datetime,
                         const std::string &p_target) : datetime(p_datetime),
                                                        type("SIGNAL"),
                                                        target(p_target),
                                                        location("STACK"),
                                                        symbol(p_symbol),
                                                        percentage(p_percentage) {}

// Order Event initializer list
OrderEvent::OrderEvent(const std::string &p_symbol, const double p_percentage, const unsigned long p_datetime,
                       const std::string &p_target, const std::string &p_location) : datetime(p_datetime),
                                                                                     type("ORDER"),
                                                                                     target(p_target),
                                                                                     location(p_location),
                                                                                     symbol(p_symbol),
                                                                                     percentage(p_percentage) {}

// Fill Event initializer list
FillEvent::FillEvent(const std::string &p_symbol, const int p_quantity, const double p_cost, const double p_slippage,
                     const double p_commission, const unsigned long p_datetime, const std::string &p_target,
                     const std::string &p_location) : datetime(p_datetime),
                                                      type("FILL"),
                                                      target(p_target),
                                                      location("STACK"),
                                                      symbol(p_symbol),
                                                      quantity(p_quantity),
                                                      cost(p_cost),
                                                      slippage(p_slippage),
                                                      commission(p_commission) {}