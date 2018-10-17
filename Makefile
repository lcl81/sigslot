#
# Created by Cyberman Wu on Jul 7th, 2010.
#

CC       = g++ $(CXXFLAGS)
#CC       = gcc
#CC      = tile-gcc
#CXX     = tile-g++
#AR      = tile-ar
#RANLIB  = tile-ranlib
#STRIP   = tile-strip
#SIM     = tile-sim
#MONITOR = tile-monitor

CXXFLAGS = -Wall -g -std=c++11
#LIBS= -lpthread -lnetio -ltmc

TARGET=$(shell basename `pwd`)
SOURCES=$(wildcard *.cpp *.c)
OBJS=$(SOURCES:%.c=%.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o
