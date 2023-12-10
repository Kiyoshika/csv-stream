CC := gcc

C_STD := -std=c99

SRC_DIR := src
INCLUDE_DIR := include

CFLAGS_RELEASE="-O2 -Wall -Wextra"
CFLAGS_DEBUG="-O0 -Wall -Wextra -g"

INCLUDE_FLAGS := -I$(INCLUDE_DIR)

LINK_FLAGS := -lm
TEST_LINK_FLAGS := -lcstream $(LINK_FLAGS)

LIB_DIR := lib/

BUILD_TYPE?=Release

ifeq ($(BUILD_TYPE), Debug)
$(info ***** COMPILING IN DEBUG MODE *****)
CFLAGS=$(CFLAGS_DEBUG)
else ifeq ($(BUILD_TYPE), Release)
$(info ***** COMPILING IN RELEASE MODE *****)
CFLAGS=$(CFLAGS_RELEASE)
else
$(info ***** UNKNOWN MODE, DEFAULTING TO RELEASE MODE *****)
CFLAGS=$(CFLAGS_RELEASE)
endif

build:
	@$(CC) $(C_STD) -c $(SRC_DIR)/* $(INCLUDE_FLAGS) $(LINK_FLAGS)
	@ar -crs libcstream.a *.o
	@mv libcstream.a $(LIB_DIR)/libcstream.a
	@rm *.o

format:
	./format.sh

# view all TODO comments in the project
todo:
	grep TODO -r . --exclude Makefile

COMMON_TEST_OPTIONS := $(INCLUDE_FLAGS) -L$(LIB_DIR) $(TEST_LINK_FLAGS)
TEST_DIR := tests
test: build test-cell test-cstream

TEST_CELL_DIR := $(TEST_DIR)/cell
test-cell: build
	@$(CC) $(C_STD) -o $(TEST_CELL_DIR)/test_cell_conversions $(TEST_CELL_DIR)/conversions.c $(COMMON_TEST_OPTIONS)
	./$(TEST_CELL_DIR)/test_cell_conversions

TEST_CSTREAM_DIR := $(TEST_DIR)/cstream
test-cstream: build
	@$(CC) $(C_STD) -o $(TEST_CSTREAM_DIR)/test_full_stream $(TEST_CSTREAM_DIR)/full_stream.c $(COMMON_TEST_OPTIONS)
	./$(TEST_CSTREAM_DIR)/test_full_stream
