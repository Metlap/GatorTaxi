#include "MinHeap.h"
#include <stdexcept>


MinHeap::MinHeap() {
}


/*Checks path from newly inserted node upto the parent*/
void MinHeap::heapifyUp(int index) {
	
	//If index node is the only node in the heap, then no need of heapify
	if (index == MIN_HEAP_FIRST_INDEX) {
		return;
	}
	// Parent index = n, then child indices are 2*n +1 and 2*n + 2
	int parentIndex = (index - 1) / 2;
	bool isIndexElementSmaller = Ride::compareCostsOfRides(minHeapRides[index], minHeapRides[parentIndex]);
	if (isIndexElementSmaller) {
		Ride* temp = minHeapRides[parentIndex];
		// Swapping parent node and index nodes and recursively calling heapify up on parent node
		std::swap(minHeapRides.at(index), minHeapRides.at(parentIndex));
		std::swap(minHeapRides.at(index)->minHeapIndex, minHeapRides.at(parentIndex)->minHeapIndex);

		/*minHeapRides[parentIndex] = minHeapRides[index];
		minHeapRides[index] = temp;*/

		heapifyUp(parentIndex);
	}
	else {
		return;
	}

}

/* Called after a remove min operation to */
void MinHeap::heapifyDown(int index) {

	int currentHeapSize = minHeapRides.size();
	int leftChildIndex = 2 * index + 1;
	int rightChildIndex = 2 * index + 2;

	// Now we need to check if the left and right pointers actually exist. If they dont then no need to recursively do heapify down
	if (leftChildIndex >= currentHeapSize || rightChildIndex >= currentHeapSize) {
		return;
	}

	// If children exist, then swap the current node with the smallest of them
	int smallestIndex = index;
	bool isSmaller = Ride::compareCostsOfRides(minHeapRides[leftChildIndex], minHeapRides[index]);

	if ((leftChildIndex < currentHeapSize) && isSmaller) {
		smallestIndex = leftChildIndex;
	}

	isSmaller = Ride::compareCostsOfRides(minHeapRides[rightChildIndex], minHeapRides[smallestIndex]);
	if ((rightChildIndex < currentHeapSize) && isSmaller) {
		smallestIndex = rightChildIndex;
	}

	// If right/ left child is smaller, then swap it and recursively call heapify down
	if (smallestIndex != index) {
		Ride* temp = minHeapRides[index];
		minHeapRides[index] = minHeapRides[smallestIndex];
		minHeapRides[smallestIndex] = temp;
		heapifyDown(smallestIndex);
	}
}

void heapifyTopDown(std::vector<Ride*>& minHeapRides, Ride* lastLeaf) {

	//Top down heapify operation from the index of removed item
	int thisIndex, leftIndex, rightIndex;
	thisIndex = lastLeaf->minHeapIndex;
	while (1) { // top down
		leftIndex = (2 * thisIndex) + 1;
		rightIndex = (2 * thisIndex) + 2;
		if (leftIndex < minHeapRides.size()) { // this node is not leaf

			bool isSmaller = Ride::compareCostsOfRides(minHeapRides[leftIndex], minHeapRides[thisIndex]);

			if ( isSmaller) {
				thisIndex = leftIndex;
			}

			//isSmaller = Ride::compareCostsOfRides(minHeapRides[rightIndex], minHeapRides[thisIndex]);
			if ((rightIndex < minHeapRides.size()) && Ride::compareCostsOfRides(minHeapRides[rightIndex], minHeapRides[thisIndex])) {
				thisIndex = rightIndex;
			}

			if (thisIndex != lastLeaf->minHeapIndex) {
				std::swap(minHeapRides.at(thisIndex), minHeapRides.at(lastLeaf->minHeapIndex));
				std::swap(minHeapRides.at(thisIndex)->minHeapIndex, minHeapRides.at(lastLeaf->minHeapIndex)->minHeapIndex);
			}
			else break;
		}
		else break; // this node is leaf
	}

}

/*Remove min operation*/
Ride* MinHeap::getNextRide() {

	if (minHeapRides.size() == 0) {
		return NULL;
	}

	//Copy last element/ leaf to root
	Ride* smallest = minHeapRides.front();

	int lastLeafIndex = minHeapRides.size() - 1;
	Ride* lastLeaf = minHeapRides.at(lastLeafIndex);
	
	/* Called as part of heapify_down/ getNextRide operation, to copy value from last leaf node to root*/
	// copies last element to first index
	//minHeapRides[MIN_HEAP_FIRST_INDEX] = minHeapRides[lastLeafIndex]; 
	std::swap(minHeapRides.at(MIN_HEAP_FIRST_INDEX), minHeapRides.at(lastLeafIndex));
	std::swap(minHeapRides.at(MIN_HEAP_FIRST_INDEX)->minHeapIndex, minHeapRides.at(lastLeafIndex)->minHeapIndex);

	// delete the last element
	minHeapRides.pop_back(); 

	// to adjust heap property
	/*heapifyDown(MIN_HEAP_FIRST_INDEX);*/
	heapifyTopDown(minHeapRides, lastLeaf);

	return smallest;

}

void MinHeap::remove(Ride* toRemove) {

	if (minHeapRides.size() == 0) {
		return;
	}
	int lastLeafIndex = minHeapRides.size() - 1;
	Ride* lastLeaf = minHeapRides.at(lastLeafIndex);
	//Copy last element/ leaf to index of the node being removed
	std::swap(minHeapRides.at(toRemove->minHeapIndex), minHeapRides.at(lastLeafIndex));
	std::swap(minHeapRides.at(toRemove->minHeapIndex)->minHeapIndex, minHeapRides.at(lastLeafIndex)->minHeapIndex);

	// After swap, removing the last leaf that contains details of node to be removed
	minHeapRides.pop_back();

	heapifyTopDown(minHeapRides, lastLeaf);
}

/*To insert a new node in the heap*/
void MinHeap::insert(Ride* ride) {

	int newIndex = minHeapRides.size();

	if (newIndex >= 2000)
		throw std::length_error("The number of active buildings has exceeded 2000.");

	minHeapRides.push_back(ride);

	//updating the heap Index
	ride->minHeapIndex = minHeapRides.size() - 1;

	// Now heapifying up from the newly inserted node
	heapifyUp(ride->minHeapIndex);

}

/*Called incase of update call*/
void MinHeap::increasekey(Ride* ride, int additionalCost, int newTripDuration) {
	// do increase key
	ride->rideCost += additionalCost;
	ride->tripDuration = newTripDuration;
	// adjust position of the increased key
	heapifyTopDown(minHeapRides, ride);
}
