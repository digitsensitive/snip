# Variables
PROGRAM_NAME = snip

# Directory structure
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wno-missing-braces -I$(INCLUDE_DIR)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Main target: Create executable
$(PROGRAM_NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM_NAME)

# Rule to compile each .c into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(PROGRAM_NAME)
