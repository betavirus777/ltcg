CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2
SRC = ltcg_calculator.cpp
DEBUG_TARGET = ltcg_calculator_debug
RELEASE_TARGET = ltcg_calculator_release

all: debug release

debug: $(SRC)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(DEBUG_TARGET)

release: $(SRC)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(SRC) -o $(RELEASE_TARGET)

clean:
	rm -f $(DEBUG_TARGET) $(RELEASE_TARGET)

.PHONY: all debug release clean