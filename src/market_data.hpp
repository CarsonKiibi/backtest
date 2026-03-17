#pragma once
#include <vector>
#include <string>
#include "candle.hpp"

class MarketData {
public:
    explicit MarketData(std::vector<Candle> candles);

    size_t size() const;
    const Candle& operator[](size_t i) const;
    const Candle& front() const;
    const Candle& back() const;

    int date_to_index(const std::string& date) const;
    double avg_close() const;
    std::vector<double> moving_average(int window) const;

private:
    std::vector<Candle> candles_;
};
