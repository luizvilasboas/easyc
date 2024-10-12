CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lcheck -lsubunit -lm

SCR_DIR=src
INCLUDE_DIR=includes
TEST_DIR=tests
BIN_DIR=bin

SRC_FILES=$(wildcard $(SCR_DIR)/*.c)
TEST_FILES=$(wildcard $(TEST_DIR)/*_test.c)

TEST_TARGETS=$(patsubst $(TEST_DIR)/%_test.c,$(BIN_DIR)/%_test,$(TEST_FILES))

all: $(TEST_TARGETS)

$(BIN_DIR)/%_test: $(SCR_DIR)/%.c $(TEST_DIR)/%_test.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test || exit 1; done

clean:
	rm -rf $(BIN_DIR)

.PHONY: all test clean
