CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lcheck -lsubunit -lm

SCR_DIR=src
INCLUDE_DIR=includes
TEST_DIR=tests
TARGET=vector_test

SRC=$(SCR_DIR)/vector.c
TEST_SRC=$(TEST_DIR)/vector_test.c

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(TEST_SRC) $(LDFLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)

.PHONY: all test clean
