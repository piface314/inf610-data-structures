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

bin/$(TARGET): obj/main.o obj/list.o obj/stack.o obj/queue.o
	$(CC) -o bin/$(TARGET) obj/* $(LDFLAGS)

obj/main.o: src/main.cpp src/list/*.hpp src/stack/*.hpp src/queue/*.hpp
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

obj/list.o: src/list/list.cpp src/list/list.hpp
	$(CC) -c $(CCFLAGS) src/list/list.cpp -o obj/list.o

obj/stack.o: src/stack/stack.cpp src/stack/stack.hpp
	$(CC) -c $(CCFLAGS) src/stack/stack.cpp -o obj/stack.o

obj/queue.o: src/queue/queue.cpp src/queue/queue.hpp
	$(CC) -c $(CCFLAGS) src/queue/queue.cpp -o obj/queue.o


clean:
	rm -vf obj/* bin/*
