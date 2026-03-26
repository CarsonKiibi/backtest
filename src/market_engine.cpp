#include "market_engine.hpp"
#include <iostream>
#include <algorithm>

MarketEngine::MarketEngine(const MarketData& data, Strategy& strategy, const EngineConfig& config)
    : data_(data), strategy_(strategy), config_(config)
{
    strategy_.set_config(config_);
}

void MarketEngine::run() {
    // resolve date range --> supports both exact timestamps and date prefixes
    auto find_idx = [&](const std::string& date, int default_idx, bool find_first) -> int {
        int exact = data_.date_to_index(date);
        if (exact >= 0) return exact;
        for (int i = 0; i < (int)data_.size(); i++) {
            if (data_[i].timestamp.substr(0, date.size()) >= date)
                return find_first ? i : i - 1;
        }
        return default_idx;
    };

    int start_idx = config_.start_date.empty() ? 0
                  : find_idx(config_.start_date, 0, true);
    int end_idx = config_.end_date.empty() ? (int)data_.size() - 1
                  : find_idx(config_.end_date, (int)data_.size() - 1, false);

    double cash = config_.initial_cash;
    double position = 0.0;
    bool in_position = false;

    std::vector<Trade> trades;
    std::vector<double> equity_curve;

    for (int i = start_idx; i <= end_idx; ++i) {
        const auto& candle = data_[i];
        double price = candle.close;

        Signal signal = strategy_.generate_signal(i);

        if (signal == Signal::Buy && !in_position) {
            double spend = cash * config_.trade_fraction;
            position = spend / price;
            cash -= spend;
            in_position = true;
            trades.push_back({candle.timestamp, price, "BUY"});
        } else if (signal == Signal::Sell && in_position) {
            cash += position * price;
            position = 0.0;
            in_position = false;
            trades.push_back({candle.timestamp, price, "SELL"});
        }

        double equity = cash + position * price;
        equity_curve.push_back(equity);

        if (config_.gain_threshold > 0 && equity >= config_.initial_cash + config_.gain_threshold) {
            std::cout << "Gain threshold hit at " << candle.timestamp
                      << " (equity: " << equity << ")\n";
            break;
        }
        if (config_.loss_threshold > 0 && equity <= config_.initial_cash - config_.loss_threshold) {
            std::cout << "Loss threshold hit at " << candle.timestamp
                      << " (equity: " << equity << ")\n";
            break;
        }
    }

    double final_equity = equity_curve.empty() ? config_.initial_cash : equity_curve.back();
    double pnl = final_equity - config_.initial_cash;

    std::cout << "Date range:    " << data_[start_idx].timestamp
              << " -> " << data_[end_idx].timestamp << "\n";
    std::cout << "Initial cash:  $" << config_.initial_cash << "\n";
    std::cout << "Final equity:  $" << final_equity << "\n";
    std::cout << "P&L:           $" << pnl << " ("
              << (pnl / config_.initial_cash * 100.0) << "%)\n";
    std::cout << "Trades:        " << trades.size() << "\n";
}
