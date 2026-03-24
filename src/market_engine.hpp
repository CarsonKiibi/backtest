#pragma once
#include "market_data.hpp"
#include "strategy.hpp"

struct Trade {
    std::string timestamp;
    double price;
    std::string side; // "BUY" or "SELL"
};

class MarketEngine {
public:
    explicit MarketEngine(const MarketData& data, Strategy& strategy) : data_(data), strategy(strategy) {};
    virtual ~MarketEngine() = default;

    virtual void run() = 0;

protected:
    const MarketData& data_;
    Strategy& strategy;
};
