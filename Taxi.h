#pragma once

#ifndef TAXI_H
#define TAXI_H

#include "MinHeap.h"
#include "RBTree.h"
#include "IOterm.h"
#include <fstream>

class Taxi {
public:
	std::vector<IOterm*> actionList;
	MinHeap* minHeap;
	RBTree* rbTree;

	Taxi();

	void insertRide(int rideNumber, int rideCost, int tripDuration, std::ofstream& outFile);
	void printRide(int rideNumber, std::ofstream& outFile);
	void printRidesInRange(int rideNumber1, int rideNumber2, std::ofstream& outFile);
	void updateTrip(int rideNumber, int newTripDuration);
	void cancelRide(int rideNumber);
	void getNextRide(std::ofstream& outFile);
	void readInputFromFile(std::string, std::vector<IOterm*>& actionList);
	void takeAction(std::ofstream& outfile);
	
};


#endif // !TAXI_H
