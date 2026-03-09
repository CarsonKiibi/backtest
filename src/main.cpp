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

    auto ma10 = csv_handler.moving_average(data, 10);

    std::cout << "MA10 at index 100: " << ma10[100] << "\n";

    return EXIT_SUCCESS;
}