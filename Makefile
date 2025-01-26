CC = g++
CFLAGS = -std=c++17 -Wall -g

SRCS = test.cpp Vector.cpp
OBJS = $(SRCS:.cpp=.o)

EXEC = vector

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all

.PHONY: all clean rebuild