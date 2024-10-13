CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lcheck -lsubunit -lm

SRC_DIR=src
INCLUDE_DIR=includes
TEST_DIR=tests
BIN_DIR=bin
SUB_DIRS=$(BIN_DIR)/data_structures

SRC=$(shell find $(SRC_DIR) -name '*.c')
TEST_SRC=$(shell find $(TEST_DIR) -name '*_test.c')

BINARIES=$(patsubst $(TEST_DIR)/%_test.c, $(BIN_DIR)/%_test, $(TEST_SRC))

all: $(SUB_DIRS) $(BINARIES)

$(BIN_DIR)/%_test: $(SRC_DIR)/%.c $(TEST_DIR)/%_test.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LDFLAGS)

$(SUB_DIRS):
	mkdir -p $@

test: all
	@for test_bin in $(BINARIES); do \
		echo "Running $$test_bin..."; \
		./$$test_bin; \
	done

clean:
	rm -rf $(BIN_DIR)

.PHONY: all test clean
