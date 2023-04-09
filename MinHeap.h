#ifndef MINHEAP_H
#define MINHEAP_H

#include "Ride.h"
#include <vector>

//#define MAX_SIZE_MIN_HEAP 2000


/*Class for min heap
 int heapleft(int);
 int heapright(int);
 int heapparent(int);
*/
class MinHeap {
public:
	
	MinHeap();

	//vector field to store the rides
	std::vector<Ride*> minHeapRides;
	/* inserts new node in the MinHeap and this includes the
		 heapify_up to adjust heap property */
	void insert(Ride*);

	/*Called incase of update Function*/
	void increasekey(Ride* ride, int newTripDuration);

	/* getNextRide performs the Remove min operation - pops topmost Ride Node and returns it
		This also includes a heapify_down step to place the last element in left subtree at node and then heapify*/
	Ride* getNextRide();

	/* Called after an insert method, to check if the newly inserted node has to bubble up to the root
	*/
	void heapifyUp(int index);

	/* Called after remove min operation. The largest element in the left subtree is placed in root after deleting the old root(min element).
	* Then heapify is done downwards from root 
	*/
	void heapifyDown(int index);

	/*Used to remove the ride from MinHeap. 
	Called incase of random Remove operation when performing 
	Cancel Ride(rideNumber)*/
	void remove(Ride* toRemove);

};

#endif // !MINHEAP_H