# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/bfs

# Default rule
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Rules to compile source files into object files
$(BUILD_DIR)/decipherFile.o: $(SRC_DIR)/decipherFile.c $(INC_DIR)/decipherFile.h $(INC_DIR)/types.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/logic.o: $(SRC_DIR)/logic.c $(INC_DIR)/logic.h $(INC_DIR)/types.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/decipherFile.h $(INC_DIR)/logic.h $(INC_DIR)/types.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Run the program with the data file
run: $(TARGET)
	@$(TARGET)

# Phony targets
.PHONY: all clean run
