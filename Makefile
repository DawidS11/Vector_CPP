CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRCS = test.cpp
OBJS = test.o

EXEC = vector

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

test.o: test.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all

.PHONY: all clean rebuild