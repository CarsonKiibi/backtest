#pragma once
#include "market_engine.hpp"
#include "strategy.hpp"
#include <iostream>

void MarketEngine::run() {

    double cash = 10000.0;
    double position = 0.0;
    bool in_position = false;

    std::vector<Trade> trades;
    std::vector<double> equity_curve;

    for (size_t i = 0; i < data_.size(); ++i) {

        const auto& candle = data_[i];
        double price = candle.close;

        Signal signal = strategy.generate_signal(i);

        if (signal == Signal::Buy && !in_position) {
            position = cash / price;
            cash = 0;
            in_position = true;

            trades.push_back({candle.timestamp, price, "BUY"});

        } else if (signal == Signal::Sell && in_position) {
            cash = position * price;
            position = 0;
            in_position = false;

            trades.push_back({candle.timestamp, price, "SELL"});
        }

        // calculate equity
        double equity = cash + position * price;
        equity_curve.push_back(equity);
    }

    std::cout << "Final equity: " << equity_curve.back() << "\n";
    std::cout << "Number of trades: " << trades.size() << "\n";
}