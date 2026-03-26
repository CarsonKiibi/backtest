#pragma once
#include "market_data.hpp"
#include "strategy.hpp"
#include <vector>

struct Trade {
    std::string timestamp;
    double price;
    std::string side; // "BUY" or "SELL"
};

class MarketEngine {
public:
    MarketEngine(const MarketData& data, Strategy& strategy, const EngineConfig& config);
    void run();

private:
    const MarketData& data_;
    Strategy& strategy_;
    EngineConfig config_;
};
