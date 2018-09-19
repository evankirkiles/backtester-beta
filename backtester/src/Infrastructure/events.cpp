//
// Created by Evan Kirkiles on 7/6/18.
//

#include "backtester/include/events.hpp"

// Initializer lists for the construction of each Event Type

// Scheduled Event initializer list
ScheduledEvent::ScheduledEvent(void (*p_function), Strategy& instance, unsigned long p_datetime) :
                                                        datetime(p_datetime),
                                                        type("SCHEDULED"),
                                                        function(p_function),
                                                        stratInstance(instance){}

// Market Event initializer list
MarketEvent::MarketEvent(const std::vector<std::string>& p_symbols, const std::unordered_map<std::string, double>& p_data,
                         unsigned long p_datetime) : datetime(p_datetime),
                                                     type("MARKET"),
                                                     symbols(p_symbols),
                                                     data(p_data)  {}

// Signal Event initializer list
SignalEvent::SignalEvent(std::string p_symbol, const double p_percentage, const unsigned long p_datetime) :
                                                        datetime(p_datetime),
                                                        type("SIGNAL"),
                                                        symbol(std::move(p_symbol)),
                                                        percentage(p_percentage) {}

// Order Event initializer list
OrderEvent::OrderEvent(std::string p_symbol, const int p_quantity, const unsigned long p_datetime) :
                                                        datetime(p_datetime),
                                                        type("ORDER"),
                                                        symbol(std::move(p_symbol)),
                                                        quantity(p_quantity) {}

// Fill Event initializer list
FillEvent::FillEvent(std::string p_symbol, const int p_quantity, const double p_cost, const double p_slippage,
                     const double p_commission, const unsigned long p_datetime) :
                                                      datetime(p_datetime),
                                                      type("FILL"),
                                                      symbol(std::move(p_symbol)),
                                                      quantity(p_quantity),
                                                      cost(p_cost),
                                                      slippage(p_slippage),
                                                      commission(p_commission) {}