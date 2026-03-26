#include <cstdlib>
#include <iostream>
#include "data_handler.hpp"
#include "market_data.hpp"
#include "ma_strategy.hpp"
#include "market_engine.hpp"

int main() {
    DataHandler handler;
    MarketData data = handler.load_csv("data/Bitcoin_BTCUSDT.csv");

    // Short MA crosses above long MA = Buy, below = Sell
    // params (data, short window, long window)
    const int short_window = 10;
    const int long_window = 50;
    MovingAverageStrategy strategy(data, short_window, long_window);

    EngineConfig config;
    config.initial_cash   = 10000.0;
    config.gain_threshold = 1000.0;  // stop if up $1000
    config.loss_threshold = 1000.0;  // stop if down $1000
    config.trade_fraction = 0.25;    // use 25% of cash per trade
    config.start_date     = "2018-01-01";
    config.end_date       = "2018-12-31";

    MarketEngine engine(data, strategy, config);
    engine.run();

    return EXIT_SUCCESS;
}
