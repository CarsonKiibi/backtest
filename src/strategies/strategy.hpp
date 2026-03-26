#pragma once
#include "../engine_config.hpp"

enum class Signal {
    Buy,
    Sell,
    Hold
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
