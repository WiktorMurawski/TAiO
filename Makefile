# Compiler and Flags
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -O2
CPPFLAGS := -MMD -MP

# Directories
SRC_DIR  := src
OBJ_DIR  := obj

# Files
SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)

# Detect Operating System
ifeq ($(OS),Windows_NT)
    TARGET   := program.exe
    RM_DIR   := rmdir /s /q
    RM_FILE  := del /q
    MKDIR_CMD = @if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
else
    TARGET   := program
    RM_DIR   := rm -rf
    RM_FILE  := rm -f
    MKDIR_CMD = @mkdir -p $(OBJ_DIR)
endif

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	$(MKDIR_CMD)

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(OBJ_DIR) $(RM_DIR) $(OBJ_DIR)
	@if exist $(TARGET) $(RM_FILE) $(TARGET)
else
	$(RM_DIR) $(OBJ_DIR) $(TARGET)
endif

# Include compiler-generated dependency files
-include $(DEPS)

.PHONY: all clean
