src = $(wildcard *.c)
cpp_src = $(wildcard *.cpp)
targets = $(patsubst %.c, %, $(src))
cpp_targets = $(patsubst %.cpp, %, $(cpp_src))

CXX = g++
CC = gcc
CFLAGS = -Wall -g -lpthread  -std=c++11

all:$(targets) $(cpp_targets)
	@echo $(targets)

$(targets):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

$(cpp_targets):%:%.cpp
	$(CXX) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) $(cpp_targets) a.out

