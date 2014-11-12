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

INCLUDE_DIR = -I./include
BUILD_DIR = target

TEST_BIN = reflect_test
TEST_SRC_DIR = example
TEST_SRCS = $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJS = $(subst .cpp,.o,$(TEST_SRCS))

CXXFLAGS = $(INCLUDE_DIR) --std=c++11

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC)  -o $(BUILD_DIR)/$(TEST_BIN) $(TEST_OBJS)

clean:
	$(RM) $(TEST_OBJS)

fclean: clean
	$(RM) $(BUILD_DIR)

re: fclean all
