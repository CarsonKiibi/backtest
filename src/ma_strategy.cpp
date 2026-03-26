#include "ma_strategy.hpp"

MovingAverageStrategy::MovingAverageStrategy(
    const MarketData& data,
    int short_window,
    int long_window
) : short_ma(data.moving_average(short_window)),
    long_ma(data.moving_average(long_window))
{}

Signal MovingAverageStrategy::generate_signal(int i) {
    if (i < 0 || i >= (int)long_ma.size() || long_ma[i] == 0.0)
        return Signal::Hold;

    if (short_ma[i] > long_ma[i])
        return Signal::Buy;

    if (short_ma[i] < long_ma[i])
        return Signal::Sell;

    return Signal::Hold;
}
