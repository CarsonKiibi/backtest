#pragma once
#include "market_data.hpp"

class MarketEngine {
public:
    explicit MarketEngine(const MarketData& data) : data_(data) {}
    virtual ~MarketEngine() = default;

    virtual void run() = 0;

protected:
    const MarketData& data_;
};
