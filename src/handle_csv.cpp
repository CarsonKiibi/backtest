#include "handle_csv.hpp"
#include <fstream>
#include <sstream>

std::vector<Candle> CSV_Handler::load_csv(const std::string& path) {
    std::vector<Candle> data;

    std::ifstream file(path);
    std::string line;

    std::getline(file, line); // skip header
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;

        Candle c;

        std::getline(ss, cell, ',');
        c.timestamp = cell;

        std::getline(ss, cell, ',');
        c.open = std::stod(cell);

        std::getline(ss, cell, ',');
        c.high = std::stod(cell);

        std::getline(ss, cell, ',');
        c.low = std::stod(cell);

        std::getline(ss, cell, ',');
        c.close = std::stod(cell);

        std::getline(ss, cell, ',');
        c.volume = std::stod(cell);

        data.push_back(c);
    }

    return data;
}

double CSV_Handler::avg_close(const std::vector<Candle>& data) {
    double sum = 0;
    for (const auto& c : data) {
        sum += c.close;
    }

    return sum / data.size();
}

std::vector<double> CSV_Handler::moving_average(const std::vector<Candle>& data, int window) {
    std::vector<double> ma(data.size());
    double sum = 0;

    for (int i = 0; i < data.size(); i++) {
        sum += data[i].close;

        if (i >= window)
            sum -= data[i - window].close;

        if (i >= window - 1)
            ma[i] = sum / window;
        else 
            ma[i] = 0;
    }

    return ma;
}