#pragma once
#include <string>

enum class Signal {
    Buy,
    Sell,
    Hold
};

struct EngineConfig {
    double initial_cash    = 10000.0;
    double gain_threshold  = 0.0;   // stop if equity >= initial_cash + gain_threshold (0 = disabled)
    double loss_threshold  = 0.0;   // stop if equity <= initial_cash - loss_threshold (0 = disabled)
    double trade_fraction  = 1.0;   // fraction of cash to deploy per buy (0.0 - 1.0)
    std::string start_date = "";    // e.g. "2018-01-01", empty = from beginning
    std::string end_date   = "";    // e.g. "2018-12-31", empty = to end
};

class Strategy {
protected:
    Strategy() = default;
    EngineConfig config_;

public:
    virtual ~Strategy() = default;
    virtual Signal generate_signal(int index) = 0;
    void set_config(const EngineConfig& config) { config_ = config; }
};
