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
	/*Calls methods to insert the ride in minheap and rbtree. Prints duplicate rideNumber error onto the output file*/
	void insertRide(int rideNumber, int rideCost, int tripDuration, std::ofstream& outFile);

	/*Calls the get(rideNumber) method of rbTree class and writes the output to the output_file*/
	void printRide(int rideNumber, std::ofstream& outFile);

	/*Calls the method getRIdeNumbersInRange(rideNumber1, rideNumber2) method of rbTree class and writes the output to the output_file*/
	void printRidesInRange(int rideNumber1, int rideNumber2, std::ofstream& outFile);

	/*Update function -> UpdateTrip(rideNumber, new_tripDuration) where the rider wishes to change the destination
	 a) if the Ride =  getByRideNumber in RBT  and if new_tripDuration <= existing tripDuration,  just update the tripDuration to the new_tripDuration.
	b) if the existing_tripDuration < new_tripDuration <= 2 * (existing tripDuration), 
	increment key(rideNumber, rideCost + 10,	new_tripDuration) in Minheap
	c) if the new_tripDuration > 2 * (existing tripDuration), remove from bot*/
	void updateTrip(int rideNumber, int newTripDuration);

	/*Calls the removeByrideNumber method in rbTree and removeRandomRide in minHeap. Removes the ride from both minHeap and rbTree*/
	void cancelRide(int rideNumber);

	/*Calls the removeMin in minHeap and also removes the ride with that reideNumber from the rbTree*/
	void getNextRide(std::ofstream& outFile);

	/*Called to read the commands from the input file and store them as a vector<IOterm* >(actionList) in the Taxi object*/
	void readInputFromFile(std::string, std::vector<IOterm*>& actionList);

	/*Called when reading each action from the actionList and to call corresponding methods from rbTree and minHeap*/
	void takeAction(std::ofstream& outfile);
	
};


#endif // !TAXI_H
