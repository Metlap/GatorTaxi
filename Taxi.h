#pragma once

#ifndef TAXI_H
#define TAXI_H

#include "MinHeap.h"
#include "RBTree.h"
#include "IOterm.h"

class Taxi {
public:
	std::vector<IOterm*> actionList;
	MinHeap* minHeap;
	RBTree* rbTree;

	Taxi();

	void insertRide(int rideNumber, int rideCost, int tripDuration);
	void printRide(int rideNumber);
	void printRidesInRange(int rideNumber1, int rideNumber2);
	void updateTrip(int rideNumber, int newTripDuration);
	void cancelRide(int rideNumber);
	void getNextRide();
};
void printRideToFile(Ride* ride);
#endif // !TAXI_H
