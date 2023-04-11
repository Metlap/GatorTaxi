# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
#CC = g++
#CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
#GatorTaxi: GatorTaxi.o Taxi.o IOterm.o RBTree.o MinHeap.o Ride.o
#    $(CC) $(CFLAGS) -o GatorTaxi GatorTaxi.o Taxi.o IOterm.o RTree.o MinHeap.o Ride.o
 
# The main.o target can be written more simply
 
#GatorTaxi.o: GatorTaxi.cpp Taxi.h
#    $(CC) $(CFLAGS) -c GatorTaxi.cpp
 
#Taxi.o: Taxi.h
 
#RBTree.o: RBTree.h

#MinHeap.o: MinHeap.h

#Ride.o: Ride.h

PROGRAM = gatorTaxi
CXX = g++
CXXFLAGS = -std=c++0x

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(wildcard *.h)

default: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${PROGRAM}

clean:
	rm -f ${OBJECTS} ${PROGRAM}