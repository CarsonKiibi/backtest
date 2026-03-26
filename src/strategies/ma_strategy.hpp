#pragma once
#include "strategy.hpp"
#include "../market_data.hpp"

class MovingAverageStrategy : public Strategy {
    public:
        MovingAverageStrategy(
            const MarketData& data,
            int short_window,
            int long_window
        );

        Signal generate_signal(int i) override;

    private:
        std::vector<double> short_ma;
        std::vector<double> long_ma;
};