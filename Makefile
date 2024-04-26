CC := $(or $(shell echo $$CC),gcc)
CFLAGS := -Wall -Wextra -O2 -Iinclude -static $(shell echo $$CFLAGS)
LDFLAGS := $(shell echo $$LDFLAGS)

ifeq ($(shell echo $$STRIP), 1)
	LDFLAGS := $(LDFLAGS) -s
endif

SRC_DIR := src
OBJ_DIR := obj
TARGET := bin/init

SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	@echo "$(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$< -> $@"

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)/*
	@rm -f $(TARGET)

.PHONY: rebuild
rebuild: clean $(TARGET)

.PHONY: format
format:
	@clang-format -i $(SRC) $(shell find include -type f -name "*.hpp")

