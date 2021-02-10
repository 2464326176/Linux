G++ = g++ -std=c++11 -lpthread


src = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(src))

all: server

server: server.o wrap.o
	G++ server.o wrap.o -o ser

%.o:%.cpp
	G++ -c $< -Wall

.PHONY: clean all
clean:
	-rm -rf server client $(obj)
