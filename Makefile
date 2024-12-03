# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR := src
BIN_DIR := bin
COMMANDS_DIR := commands
STRATEGIES_DIR := strategies

# Files and build targets
EXECUTABLE := $(BIN_DIR)/green_fleet
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
STRATEGY_FILES := $(wildcard $(STRATEGIES_DIR)/*.cpp)
COMMAND_FILES := $(wildcard $(COMMANDS_DIR)/*.cpp)
OBJ_FILES := $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(SRC_FILES) $(STRATEGY_FILES) $(COMMAND_FILES)))

# Rules
all: $(BIN_DIR) $(EXECUTABLE)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(STRATEGIES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(COMMANDS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
	rmdir $(BIN_DIR) || true

.PHONY: all clean
