#pragma once
#include <string>

struct EngineConfig {
    double initial_cash    = 10000.0;
    double gain_threshold  = 0.0;
    double loss_threshold  = 0.0;
    double trade_fraction  = 1.0;
    std::string start_date = "";
    std::string end_date   = "";
};
