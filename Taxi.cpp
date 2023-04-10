#include "Taxi.h"
#include <iostream>
#include<fstream>
#include <string>

// Driver class that talks to the MinHeap and RBTree
Taxi::Taxi() {

	actionList.clear();
	this->minHeap = new MinHeap();
	this->rbTree = new RBTree();

}

/*Function to print the RBTree for debugging purposes*/
void printTree(RBNode* root, int edge = 0) {
	int tab = 10;
	if (root == nullptr) return;
	//edge += tab;
	printTree(root->right, edge);
	std::cout << std::endl;
	for (size_t i = tab; i < edge; i++) std::cout << " ";
	std::cout << root->ride->rideNumber << "(" << (root->color == RED ? "r" : "b") << ")" << std::endl;
	printTree(root->left, edge);
}

/*Function to print the MinHeap for debugging purposes*/
void printheap(MinHeap* heap, int rootind = 0, int edge = 0) {
	int tab = 10;
	if (rootind < 0 || rootind >= heap->minHeapRides.size()) return;
	//edge += tab;
	printheap(heap, 2* rootind +2, edge);
	std::cout << std::endl;
	for (size_t i = tab; i < edge; i++) std::cout << " ";
	std::cout << heap->minHeapRides.at(rootind)->rideNumber << "(" << heap->minHeapRides.at(rootind)->rideCost << ")" << std::endl;
	printheap(heap, 2*rootind+1, edge);
}

/* Called to get the action term from each line command of the input file*/
void getActionTerm(std::string line, IOterm*& thisTerm) {

	// To find the action term
	if (line.find("Insert") != std::string::npos) thisTerm->action = Insert;
	if (line.find("Print") != std::string::npos) thisTerm->action = Print;
	if (line.find("GetNextRide") != std::string::npos) thisTerm->action = GetNextRide;
	if (line.find("CancelRide") != std::string::npos) thisTerm->action = CancelRide;
	if (line.find("UpdateTrip") != std::string::npos) thisTerm->action = UpdateTrip;

	// To find the parameters
	int leftIndex = line.find_first_of("(") + 1;
	int rightIndex = line.find_last_of(")");

	std::string paramterString(line, leftIndex, rightIndex - leftIndex);
	int start = 0; int end;
	for (size_t i = 0; i < paramterString.size(); i++) {
		if (paramterString.at(i) == ',') {
			end = i;
			thisTerm->parameters.push_back(std::stoi(paramterString.substr(start, end)));
			start = i + 1;
		}
		if (i == paramterString.size() - 1)
			thisTerm->parameters.push_back(std::stoi(paramterString.substr(start, i + 1)));
	}

}


/* Method to read from input file and update the actionList field of the Taxi object*/
void Taxi::readInputFromFile(std::string fileName, std::vector<IOterm*>& actionList) {

	//Read line one by one from file
	std::string line;

	std::ifstream inFile(fileName);
	if (inFile.is_open()) {
		while (std::getline(inFile, line)) {
			IOterm* thisTerm = new IOterm();
			getActionTerm(line, thisTerm);
			actionList.push_back(thisTerm);
		}

		inFile.close();
	}
}

/*To write the output to file*/
void printRideToFile(Ride* ride, std::ofstream& outFile) {
	if (outFile.is_open()) {}
	outFile << "(" << ride->getRideNumber() << "," << ride->rideCost << "," << ride->getTripDuration() << ")";
}

/*To write the output to file*/
void printRidesToFile(std::vector<Ride*>& rides, std::ofstream& outFile) {
	if (outFile.is_open()) {
		for (size_t i = 0; i < rides.size(); i++) {
			printRideToFile(rides.at(i), outFile);
			if (i < rides.size() - 1) {
				outFile << ",";
			}
		}
		outFile << std::endl;
	}
}

void Taxi::insertRide(int rideNumber, int rideCost, int tripDuration, std::ofstream& outFile) {
	try {
		Ride* toInsert = new Ride(rideNumber, rideCost, tripDuration);
		minHeap->insert(toInsert);
		int ans = rbTree->insertRideInRBTree(toInsert);
		if (ans == 0) {
			if (outFile.is_open()) {
				outFile << "Duplicate RideNumber";
			}
			outFile.close();
		}
	}
	catch (std::invalid_argument& e) {
		if (outFile.is_open()) {
			outFile << "Duplicate RideNumber";
		}
	}
}

void Taxi::printRide(int rideNumber, std::ofstream &outFile) {
	RBNode* toPrint = rbTree->get(rideNumber);
	printRideToFile(toPrint->ride, outFile);
	outFile << std::endl;
}

void Taxi::printRidesInRange(int rideNumber1, int rideNumber2, std::ofstream& outFile) {
	std::vector<Ride*> toPrint = rbTree->getRidesInRangeFromRBTree(rideNumber1, rideNumber2);
	printRidesToFile(toPrint, outFile);
}

//Update function ->

// UpdateTrip(rideNumber, new_tripDuration) where the rider wishes to change the destination, in

// a) if the Ride =  getByRideNumber in RBT  and if new_tripDuration <= existing tripDuration, 
// just update the tripDuration to the new_tripDuration.
// b) if the existing_tripDuration < new_tripDuration <= 2 * (existing tripDuration), 
// increment key(rideNumber, rideCost + 10,	new_tripDuration) in Minheap
//	c) if the new_tripDuration > 2 * (existing tripDuration), remove from both	

void Taxi::updateTrip(int rideNumber, int newTripDuration) {

	/*std::cout << "Heap is" << std::endl;
	printheap(this->minHeap);
	std::cout << "_______________________________________________________________________________________________" << std::endl;
	std::cout << "Tree is" << std::endl;
	printTree(this->rbTree->RBTreeRoot);
	std::cout << "________________________________________________________________________________________________" << std::endl;*/

	RBNode* toUpdate = rbTree->get(rideNumber);
	Ride* toUpdateRide = toUpdate->ride;
	if (newTripDuration <= toUpdateRide->getTripDuration()) {
		minHeap->increasekey(toUpdateRide, 0, newTripDuration);
		return;
	}
	else if ((toUpdateRide->getTripDuration() < newTripDuration) && (newTripDuration <= 2 * (toUpdateRide->getTripDuration()))) {
		minHeap->increasekey(toUpdateRide, 10, newTripDuration);
		return;
	}
	else {
		if (toUpdate->ride->getRideNumber() != 0) {
			minHeap->remove(toUpdateRide);
			rbTree->removeRideFromRBTree(toUpdateRide->rideNumber);
			return;
		}

	}
}

void Taxi::cancelRide(int rideNumber) {

	RBNode* toCancel = rbTree->get(rideNumber);
	Ride* toCancelRide = toCancel->ride;
	if (toCancel->ride->getRideNumber() != 0){
		rbTree->removeRideFromRBTree(rideNumber);
		minHeap->remove(toCancelRide);
	}
}

void Taxi::getNextRide(std::ofstream& outFile) {
	Ride* nextRide = minHeap->getNextRide();
	if (nextRide == NULL){
		//Ride* next = new Ride(0, 0, 0);
		//printRideToFile(next);
		if (outFile.is_open()) {
			outFile << "No active Ride requests" << std::endl;
		}
	}
	else {
		int rideNumber = nextRide->getRideNumber();
		rbTree->removeRideFromRBTree(rideNumber);
		printRideToFile(nextRide, outFile);
		outFile << std::endl;
	}
}

void Taxi::takeAction( std::ofstream& outFile) {

	
	//std::cout << "________________________________________________________________________________________________" << std::endl;
	//std::cout << "Action is ::" << this->actionList.front()->action << std::endl;
	//std::cout << "Heap is" << std::endl;
	//printheap(this->minHeap);
	//std::cout << "_______________________________________________________________________________________________" << std::endl;
	//std::cout << "Tree is" << std::endl;
	//printTree(this->rbTree->RBTreeRoot);
	//std::cout << "________________________________________________________________________________________________" << std::endl;
	
	
	IOterm* term = this->actionList.front();
	if (term->action == Insert) {
		insertRide(term->parameters.at(0), term->parameters.at(1), term->parameters.at(2), outFile);
	}
	if (term->action == Print) {
		if (term->parameters.size() == 1)
			printRide(term->parameters.at(0), outFile);
		if (term->parameters.size() == 2)
			printRidesInRange(term->parameters.at(0), term->parameters.at(1), outFile);
	}
	if (term->action == GetNextRide) {
		getNextRide(outFile);
	}
	if (term->action == UpdateTrip) {
		updateTrip(term->parameters.at(0), term->parameters.at(1));
	}
	if (term->action == CancelRide) {
		cancelRide(term->parameters.at(0));
	}


	this->actionList.erase(actionList.begin());
}