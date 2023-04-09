#ifndef RIDE_H
#define RIDE_H

#define MAX_SIZE_MIN_HEAP 2000
#define MIN_HEAP_FIRST_INDEX 0
#define MAX_SIZE_RB_TREE 2000
#define RB_TREE_FIRST_INDEX 0

/// A class that holds the ride details including all its fields
class Ride {

public:
	// Unique integer identifier for each ride.
	int rideNumber;
	// The estimated cost(in integer dollars) for the ride.
	int rideCost;
	// the total time(in integer minutes) needed to get from pickup to destination
	int tripDuration;
	//Integer field to store the index in Minheap
	int minHeapIndex;

	// Function to initialize
	Ride(int rideNumber, int rideCost, int tripDuration, int minHeapIndex);
	Ride(int rideNumber, int rideCost, int tripDuration);
	Ride();
	int getRideNumber();
	int getRideCost();
	int getTripDuration();
	int getMinHeapIndex();
	static bool compareCostsOfRides(Ride* r1, Ride* r2);
};


#endif // RIDE_H