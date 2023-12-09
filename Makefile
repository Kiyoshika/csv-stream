CC := gcc

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
	@$(CC) -std=c99 -c $(SRC_DIR)/* $(INCLUDE_FLAGS) $(LINK_FLAGS)
	@ar -crs libcstream.a *.o
	@mv libcstream.a $(LIB_DIR)/libcstream.a
	@rm *.o

TEST_DIR := tests
TEST_CELL_DIR := $(TEST_DIR)/cell
test: build
	@$(CC) -std=c99 -o test_cell_int_conversions $(TEST_CELL_DIR)/int_conversions.c $(INCLUDE_FLAGS) -L$(LIB_DIR) $(TEST_LINK_FLAGS)
	./test_cell_int_conversions
