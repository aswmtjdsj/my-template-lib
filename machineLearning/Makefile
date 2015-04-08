CC=g++
DEBUG_FLAG=-DDEBUG
CXX11FLAG=--std=c++0x
CFLAGS= -O2 -g -Wall $(CXX11FLAG) $(DEBUG_FLAG)
TARGET=solver
HEADERS=decision_tree.hpp tree_node.hpp
SRC=main.cpp

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	-rm $(TARGET) $(OBJECTS)
