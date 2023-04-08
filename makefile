TARGET := structures
CC := g++
CCFLAGS := -O2 -Wall -g -std=c++17
LDFLAGS := -Wall -lpthread -lm -ldl -lz -lncurses -rdynamic

.PHONY: all clean

all: obj bin bin/$(TARGET)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

bin/$(TARGET): obj/main.o obj/list.o obj/stack.o
	$(CC) -o bin/$(TARGET) obj/* $(LDFLAGS)

obj/main.o: src/main.cpp src/*.hpp
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

obj/list.o: src/list.cpp src/list.hpp
	$(CC) -c $(CCFLAGS) src/list.cpp -o obj/list.o

obj/stack.o: src/stack.cpp src/stack.hpp
	$(CC) -c $(CCFLAGS) src/stack.cpp -o obj/stack.o


clean:
	rm -vf obj/* bin/*
