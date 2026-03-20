CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRC := src/main.cpp src/market_data.cpp src/data_handler.cpp
TARGET := backtest

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: clean
