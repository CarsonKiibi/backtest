#include "market_data.hpp"

MarketData::MarketData(std::vector<Candle> candles)
    : candles_(std::move(candles)) {}

size_t MarketData::size() const { return candles_.size(); }

const Candle& MarketData::operator[](size_t i) const { return candles_[i]; }
const Candle& MarketData::front() const { return candles_.front(); }
const Candle& MarketData::back() const { return candles_.back(); }

int MarketData::date_to_index(const std::string& date) const {
    for (int i = 0; i < (int)candles_.size(); i++) {
        if (candles_[i].timestamp == date)
            return i;
    }
    return -1;
}

double MarketData::avg_close() const {
    double sum = 0;
    for (const auto& c : candles_)
        sum += c.close;
    return sum / candles_.size();
}

std::vector<double> MarketData::moving_average(int window) const {
    std::vector<double> ma(candles_.size(), 0.0);
    double sum = 0;
    for (int i = 0; i < (int)candles_.size(); i++) {
        sum += candles_[i].close;
        if (i >= window)
            sum -= candles_[i - window].close;
        if (i >= window - 1)
            ma[i] = sum / window;
    }
    return ma;
}
