CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lX11 -lboost_system -lboost_thread

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Include directories
INCLUDE_DIRS = -I$(SRC_DIR) -I$(SRC_DIR)/network -I.

# Source files
CLIENT_SRC = $(wildcard $(SRC_DIR)/client.cpp $(SRC_DIR)/network/*.cpp)
SERVER_SRC = $(wildcard $(SRC_DIR)/server.cpp $(SRC_DIR)/network/*.cpp)

# Object files
CLIENT_OBJ = $(CLIENT_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
SERVER_OBJ = $(SERVER_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Targets
CLIENT_TARGET = $(BIN_DIR)/client
SERVER_TARGET = $(BIN_DIR)/server

.PHONY: all clean

all: $(CLIENT_TARGET) $(SERVER_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(CLIENT_OBJ) -o $@ $(LDFLAGS)

$(SERVER_TARGET): $(SERVER_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SERVER_OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
