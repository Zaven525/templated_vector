TARGET = ./a.out	
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
SRC = main.cpp
HEADERS = header.hpp source.tpp

build: $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: build run clean
