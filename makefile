# The MIT License (MIT)
#
# Copyright (c) 2014 Jeremy Letang
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC = g++
RM = rm -rf

HOST = $(shell uname)

INCLUDE_DIR = -Iinclude
BUILD_DIR = target

TEST_BIN = reflect_test
TEST_SRC_DIR = example
TEST_SRCS = $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJS = $(subst .cpp,.o,$(TEST_SRCS))

CXXFLAGS = -Wall --std=c++11 $(INCLUDE_DIR)

ifeq ($(HOST), Darwin)
CXXFLAGS += -Wno-return-type-c-linkage
endif

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	mkdir -p $(BUILD_DIR)
ifeq ($(HOST), Linux)
	$(CC) -rdynamic -ldl -o $(BUILD_DIR)/$(TEST_BIN) $(TEST_OBJS)
endif
ifeq ($(HOST), Darwin)
	$(CC) -o $(BUILD_DIR)/$(TEST_BIN) $(TEST_OBJS)
endif

pre:
ifeq ($(HOST), Linux)
	$(CC) -rdynamic -ldl -o $(BUILD_DIR)/$(TEST_BIN) $(TEST_OBJS)
endif
ifeq ($(HOST), Darwin)
	$(CC) -E $(INCLUDE_DIR) $(TEST_SRCS)
endif

clean:
	$(RM) $(TEST_OBJS)

fclean: clean
	$(RM) $(BUILD_DIR)

re: fclean all
