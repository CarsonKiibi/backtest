#include "data_handler.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

MarketData DataHandler::load_csv(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + path);

    std::vector<Candle> candles;
    std::string line;

    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        Candle c;

        std::getline(ss, cell, ','); c.timestamp = cell;
        std::getline(ss, cell, ','); c.open      = std::stod(cell);
        std::getline(ss, cell, ','); c.high      = std::stod(cell);
        std::getline(ss, cell, ','); c.low       = std::stod(cell);
        std::getline(ss, cell, ','); c.close     = std::stod(cell);
        std::getline(ss, cell, ','); c.volume    = std::stod(cell);

        candles.push_back(c);
    }

    return MarketData(std::move(candles));
}
