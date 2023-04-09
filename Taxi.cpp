#include "Taxi.h"
#include <iostream>

Taxi::Taxi() {

	actionList.clear();
	this->minHeap = new MinHeap();
	this->rbTree = new RBTree();

}

//TODO
void printRideToFile(Ride* ride) {
	//if (outFile.is_open()) {}
	std::cout << "(" << ride->getRideNumber() << "," << ride->rideCost << "," << ride->getTripDuration() << ")";
}

//TODO
 /*std::ofstream& outfile*/
void printRidesToFile(std::vector<Ride*>& rides) {
	//if (outfile.is_open()) {
		for (size_t i = 0; i < rides.size(); i++) {
			printRideToFile(rides.at(i));
			if (i < rides.size() - 1) {
				std::cout << ",";
			}
		}
		std::cout << std::endl;
	//}
}

void Taxi::insertRide(int rideNumber, int rideCost, int tripDuration) {
	Ride* toInsert = new Ride(rideNumber, rideCost, tripDuration);
	minHeap->insert(toInsert);
	rbTree->insertRideInRBTree(toInsert);
	
}

// Need to add output file here
//TODO
void Taxi::printRide(int rideNumber) {
	RBNode* toPrint = rbTree->get(rideNumber);
	printRideToFile(toPrint->ride);
	std::cout << std::endl;
}

//TODO
void Taxi::printRidesInRange(int rideNumber1, int rideNumber2) {
	std::vector<Ride*> toPrint = rbTree->getRidesInRangeFromRBTree(rideNumber1, rideNumber2);
	printRidesToFile(toPrint);
}

//Update function ->

// UpdateTrip(rideNumber, new_tripDuration) where the rider wishes to change the destination, in

// a) if the Ride =  getByRideNumber in RBT  and if new_tripDuration <= existing tripDuration, there would be no action needed.
// 
// b) if the existing_tripDuration < new_tripDuration <= 2 * (existing tripDuration), 
// increment key(rideNumber, rideCost + 10,	new_tripDuration) in Minheap

//	c) if the new_tripDuration > 2 * (existing tripDuration), remove from both	

void Taxi::updateTrip(int rideNumber, int newTripDuration) {
	RBNode* toUpdate = rbTree->get(rideNumber);
	Ride* toUpdateRide = toUpdate->ride;
	if (newTripDuration <= toUpdateRide->getTripDuration()) {
		return;
	}
	else if ((toUpdateRide->getTripDuration() < newTripDuration) && (newTripDuration <= 2 * (toUpdateRide->getTripDuration()))) {
		minHeap->increasekey(toUpdateRide);
		return;
	}
	else {
		minHeap->remove(toUpdateRide);
		rbTree->removeRideFromRBTree(toUpdateRide->rideNumber);
		return;
	}
}

void Taxi::cancelRide(int rideNumber) {

	RBNode* toCancel = rbTree->get(rideNumber);
	Ride* toCancelRide = toCancel->ride;
	rbTree->removeRideFromRBTree(rideNumber);
	minHeap->remove(toCancelRide);
}

void Taxi::getNextRide() {
	Ride* nextRide = minHeap->getNextRide();
	if (nextRide == NULL){
		//Ride* next = new Ride(0, 0, 0);
		//printRideToFile(next);
		std::cout << "No active requests" << std::endl;
	}
	else {
		int rideNumber = nextRide->getRideNumber();
		rbTree->removeRideFromRBTree(rideNumber);
		printRideToFile(nextRide);
		std::cout << std::endl;
	}
}

