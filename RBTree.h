#pragma once
#ifndef RBTREE_H
#define RBTREE_H

#include "Ride.h"
#include <vector>
 
/* Custom list to store the node colorings in RBTree
*/
enum RBColor {
	RED,
	BLACK
};


class RBNode {
public:
	RBNode();
	RBNode(Ride* ride);

	RBNode* getLeftChild();
	RBNode* getRightChild();
	RBNode* getParentNode();
	RBNode* getSibling();

	Ride* getRide();

	int getColor();

	// Fields of the RBNode
	Ride* ride;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	int color;

};


/* RBTree Class that has RBNodes */
class RBTree {
public:
	RBNode* RBTreeRoot;
	RBTree();
	/*To insert a new ride in RBTree*/
	int insertRideInRBTree(Ride* ride);
	/*Called within insert function, to make insertion in BST tree 
	and update the parent pointer of newly inserted node */
	//void BSTInsert(RBNode* &RBTreeRoot, RBNode* node);

	std::vector<Ride*> getRidesInRangeFromRBTree(int rideNumber1, int rideNumber2);
	//int compareRideNumbersInRBTree(RBNode* r1, RBNode* r2);

	//Get by RideNumber
	RBNode* get(int rideNumber);

	//Remove Ride from RBTree
	void removeRideFromRBTree(int rideNumber);

	/*Rotations in RBTree to fix violations and make the tree balanced*/
	/*void rotateLeft(RBNode*& root, RBNode*& pt);
	void rotateRight(RBNode*& root, RBNode*& pt);
	void fixViolation(RBNode*& root, RBNode*& node);
	RBNode* STInsert(RBNode* root, RBNode* node);*/

};
#endif // !RBTREE_H
