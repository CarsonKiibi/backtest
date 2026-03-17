#pragma once
#include <string>
#include "market_data.hpp"

class DataHandler {
public:
    MarketData load_csv(const std::string& path) const;
};
