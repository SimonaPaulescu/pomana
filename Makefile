CC = gcc
CPPFLAGS = -D__USE_BSD -D_GNU_SOURCE
CFLAGS = -Wall -g -std=c99
LDLIBS = -lm
HEADERS = graph.h

.PHONY: all clean

all: part1 part2

%.o: $(HEADERS)

part1: part1.o graph_functions.o graph_search.o


clean:
	-rm -f *~
	-rm -f part1.o part2.o graph_functions.o graph_search.o queue_functions.o
	-rm -f part1 part2
