CC       := cc
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -O2 -g -I.
LDLIBS   := -lm
AR       := ar

BUILD    := build
SRC_DIR  := src
TEST_DIR := tests

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(SRCS))

TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(BUILD)/%,$(TEST_SRCS))

LIB := $(BUILD)/libmllhep.a

.PHONY: all lib test clean

all: lib

lib: $(LIB)

$(LIB): $(OBJS) | $(BUILD)
	$(AR) rcs $@ $(OBJS)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%: $(TEST_DIR)/%.c $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) $< $(OBJS) $(LDLIBS) -o $@

$(BUILD):
	mkdir -p $(BUILD)

test: $(TEST_BINS)
	@fail=0; for t in $(TEST_BINS); do ./$$t || fail=1; done; exit $$fail

clean:
	rm -rf $(BUILD)
