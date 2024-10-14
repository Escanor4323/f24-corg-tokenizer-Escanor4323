# Makefile

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11 -I src

# Directories
SRC_DIR = src

# Source Files for Main Executable
MAIN_SRCS = main.c $(SRC_DIR)/tokenizer.c $(SRC_DIR)/history.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
MAIN_TARGET = tokenizer

# Source Files for Tester Executable
TEST_SRCS = $(SRC_DIR)/tester.c $(SRC_DIR)/tokenizer.c $(SRC_DIR)/history.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_TARGET = tester

# Default Target
all: $(MAIN_TARGET) $(TEST_TARGET)

# Link Main Executable
$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

# Link Tester Executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Artifacts
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

# Phony Targets
.PHONY: all clean tester

# Optional: Separate Tester Build
tester: $(TEST_TARGET)