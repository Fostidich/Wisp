CC = g++
CFLAGS = -std=c++11 -Wall -I./include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/wisp
SRCS = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
