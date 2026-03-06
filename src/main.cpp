#include <cstdlib>
#include <iostream>
#include "handle_csv.hpp"

int main() {
    CSV_Handler csv_handler{};
    auto data = csv_handler.load_csv("data/Bitcoin_BTCUSDT.csv");

    std::cout << "Loaded rows: " << data.size() << "\n";

    std::cout << "First close price: " << data[0].close << "\n";
    std::cout << "Last close price: " << data.back().close << "\n";

    std::cout << "Average close: " << csv_handler.avg_close(data) << "\n";

    return EXIT_SUCCESS;
}