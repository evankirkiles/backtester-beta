//
// Created by Evan Kirkiles on 7/10/18.
//

#include <utility>
#include "backtester/include/portfolio.hpp"

// Portfolio class functions
// Portfolio constructor initializing the empty maps for which to fill with holdings and positions data.
//
// @param p_symbol_list       a vector of the symbols on which the algorithm operates
// @param p_initial_capital   the initial capital, in dollars, on which the algorithm operates
// @param p_start_date        a unix timestamp of the backtest start date
// @param p_stack_eventqueue  a pointer to the strategy's stack queue (events which are executed immediately)
// @param p_heap_eventlist    a pointer to the strategy's heap list (events which have a specific date)
//
Portfolio::Portfolio(std::vector<std::string> p_symbol_list, unsigned int p_initial_capital, unsigned long p_start_date,
                     std::queue<Event*>* const p_stack_eventqueue, std::list<Event*>* const p_heap_eventlist) :
        symbol_list(std::move(p_symbol_list)),
        initial_capital(p_initial_capital),
        start_date(p_start_date),
        stack_eventqueue(p_stack_eventqueue),
        heap_eventlist(p_heap_eventlist) {

    // Call reset_portfolio to limit code duplication when building the empty holdings and positions
    reset_portfolio(p_initial_capital, p_start_date);
}

// Rebuilds the portfolio with a starting positions and holdings of 0 in all symbols as well as total capital
// equal to the inital capital. Used for resetting the portfolio mainly after changing a backtest variable.
//
// @param initial_capital     the initial capital to run the backtest on
// @param start_date          a unix timestamp of the backtest start date
//
void Portfolio::reset_portfolio(unsigned int initial_capital, unsigned long start_date) {

    // Clear all the maps before writing into them
    all_positions.clear();
    current_positions.clear();
    all_holdings.clear();
    current_holdings.clear();

    // Build the empty maps from the symbol list
    for (const std::string& symbol : symbol_list) {
        // Positions-related maps
        all_positions[start_date][symbol] = 0;
        current_positions[symbol] = 0;
        // Holdings-related maps
        all_holdings[start_date][symbol] = 0;
        current_holdings[symbol] = 0;
    }

    // Add the non-symbol related rows into the holdings maps as well
    all_holdings[start_date]["heldcash"] = initial_capital;
    all_holdings[start_date]["commission"] = 0;
    all_holdings[start_date]["slippage"] = 0;
    all_holdings[start_date]["totalholdings"] = initial_capital;
    all_holdings[start_date]["returns"] = 0;
    all_holdings[start_date]["equitycurve"] = 0;
    current_holdings["heldcash"] = initial_capital;
    current_holdings["commission"] = 0;
    current_holdings["slippage"] = 0;
    current_holdings["totalholdings"] = initial_capital;

    // Finally, clear the performance map
    performance_map.clear();
}

// Interprets the data from a market event and updates the holdings to reflect the latest price changes.
//
// @param marketEvent          an Event class (which is a marketEvent) that contains the data of the price changes
//
void Portfolio::update_market(Event *marketEvent) {
    // First downcast the Event so its MarketEvent members can be accessed
    auto event = dynamic_cast<MarketEvent*>(marketEvent);
    const long date = event->datetime;
    // Also forward fill the holdings from the previous date in case of non-updated symbols
    all_holdings[date] = all_holdings.end().operator->().second;

    // Get the data from the market event and update the current holdings
    for (const std::string& symbol : event->symbols) {
        const double newValuation = current_positions[symbol] * event->data.at(symbol);
        current_holdings[symbol] = newValuation;
        // Also put the updated holdings data into the all_holdings object
        all_holdings[date][symbol] = newValuation;
    }

    // Now iterate through the holdings data to calculate total holdings, returns, and equity curve
    double total_holdings = all_holdings[date]["heldcash"];
    for (const std::string& symbol : symbol_list) { total_holdings += all_holdings[date][symbol]; }
    current_holdings["totalholdings"] = total_holdings;
    // Wait off slightly on updating the total holdings of this date so as to get the previous curve and totals
    double returns = (total_holdings / all_holdings[date]["totalholdings"]) - 1;
    all_holdings[date]["totalholdings"] = total_holdings;

    // Finally, use the total holdings to calculate the returns and the equity curve
    all_holdings[date]["returns"] = returns;
    all_holdings[date]["equitycurve"] = (all_holdings[date]["equitycurve"] + 1) * (returns + 1) - 1;
}

// Interprets the data from a fill event and updates the positions (and fill-related holdings). A fill event
// contains information about commission, slippage, and the transaction cost. Also, it relays the quantity
// change in the filled stock.
//
// @param fillEvent            an Event class (which is a fillEvent) that contains the fill information
//
void Portfolio::update_fill(Event *fillEvent) {
    // First downcast the Event so its FillEvent members can be accessed
    auto event = dynamic_cast<FillEvent*>(fillEvent);

}