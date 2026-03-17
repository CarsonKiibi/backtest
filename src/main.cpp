#include <cstdlib>
#include <iostream>
#include "data_handler.hpp"
#include "market_data.hpp"

int main() {
    DataHandler handler;
    MarketData data = handler.load_csv("data/Bitcoin_BTCUSDT.csv");

    std::cout << "Loaded rows: " << data.size() << "\n";
    std::cout << "First close price: " << data.front().close << "\n";
    std::cout << "Last close price: " << data.back().close << "\n";
    std::cout << "Average close: " << data.avg_close() << "\n";

    auto ma10 = data.moving_average(10);
    std::cout << "MA10 at index 100: " << ma10[100] << "\n";
    std::cout << "Example time: " << data[100].timestamp << "\n";

    return EXIT_SUCCESS;
}
