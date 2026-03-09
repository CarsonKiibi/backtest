#include <vector>
#include <string>

struct Candle {
    std::string timestamp;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

class CSV_Handler {
    public:
        virtual std::vector<Candle> load_csv(const std::string& path);
        double avg_close(const std::vector<Candle>& data);
        std::vector<double> moving_average(const std::vector<Candle>& data, int window);
        
    private:

};