CXX = g++
CXXFLAGS = -std=c++11
SRC_DIR = src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/tabuScheduler.cpp $(SRC_DIR)/vnsScheduler.cpp $(SRC_DIR)/workflow.cpp
TARGET = main.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)