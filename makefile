TARGET := structures
CC := g++
CCFLAGS := -O2 -Wall -g -std=c++17
LDFLAGS := -Wall -lpthread -lm -ldl -lz -lncurses -rdynamic
STRUCTURES := list stack queue deque heap tree
OBJS := $(addprefix obj/,$(addsuffix .o,$(STRUCTURES)))
HEADERS := $(addprefix src/,$(addsuffix /*.hpp,$(STRUCTURES)))

.PHONY: all clean

all: obj bin bin/$(TARGET)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

bin/$(TARGET): obj/main.o $(OBJS)
	$(CC) -o bin/$(TARGET) obj/main.o $(OBJS) $(LDFLAGS)

obj/main.o: src/main.cpp $(HEADERS)
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

.SECONDEXPANSION:
obj/%.o: src/$$*/$$*.cpp src/$$*/$$*.hpp
	$(CC) -c $(CCFLAGS) src/$*/$*.cpp -o obj/$*.o

clean:
	rm -vf obj/* bin/*
