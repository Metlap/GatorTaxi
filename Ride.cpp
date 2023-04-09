#include "Ride.h"

Ride::Ride() {
}
/* Parameterised constructor */
Ride::Ride(int rideNumber, int rideCost, int tripDuration)
{
    this->rideNumber = rideNumber;
    this->rideCost = rideCost;
    this->tripDuration = tripDuration;
    this->minHeapIndex = -1;
}

Ride::Ride(int rideNumber, int rideCost, int tripDuration, int minHeapIndex)
{
    this->rideNumber = rideNumber;
    this->rideCost = rideCost;
    this->tripDuration = tripDuration;
    this->minHeapIndex = minHeapIndex;
}

int Ride::getRideNumber() {
    return this->rideNumber;
}

int Ride::getRideCost() {
    return this->rideCost;
}

int Ride::getTripDuration() {
    return this->tripDuration; 
}

int Ride::getMinHeapIndex() {
    return this->minHeapIndex;
}

// return true if r1.cost < r2.cost. If same cost, then the trip duration is used as a tie breaker
//Used as a means extract min element from the min-heap
bool Ride::compareCostsOfRides(Ride* r1, Ride* r2) {

        if (r1->getRideCost() < r2->getRideCost())
        {
            return true;
        }
        else if (r1->getRideCost() > r2->getRideCost())
        {
            return false;
        }
        else if (r1->getRideCost() == r2->getRideCost())
        {
            return (r1->getTripDuration() < r2->getTripDuration()) ? true : false;
        }

 }



