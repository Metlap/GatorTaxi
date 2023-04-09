#include "RBTree.h"
#include <iostream>
#include <string>


RBNode::RBNode(Ride* r)
{
    this->ride = r;
    this->color = RED;
    this->left = nullptr;
    this->parent = nullptr;
    this->right = nullptr;
}

//RBNode::RBNode() {
//
//    this->ride = NULL;
//    this->color = RED;
//    this->left = NULL;
//    this->parent = NULL;
//    this->right = NULL;
//}

int RBNode::getColor()
{
    return this->color;
}

RBNode* RBNode::getLeftChild()
{
    return this->left;
}

RBNode* RBNode::getRightChild()
{
    return this->right;
}

RBNode* RBNode::getParentNode()
{
    return this->parent;
}

Ride* RBNode::getRide()
{
    return this->ride;
}

RBNode* RBNode::getSibling() {

    if (parent == nullptr)
        return nullptr;
    if (this == parent->left)
        return parent->right;
    else
        return parent->left;
}

/* INITIALIZATION - incase of no rides found */
Ride* nullRide = new Ride(0, 0, 0);
RBNode* nullNode = new RBNode(nullRide);

// Tree

RBTree::RBTree()
{
    //ctor
    this->RBTreeRoot = nullptr;

}

//Print function i.e., searching by rideNumber
RBNode* RBTree::get(int rideNumber) {
    RBNode* thisNode = RBTreeRoot;
    while (1) {
        if (thisNode == nullptr) { // not found
            return nullNode;
        }
        if (rideNumber < thisNode->getRide()->getRideNumber()) // go to left
            thisNode = thisNode->left;
        else if (rideNumber > thisNode->getRide()->getRideNumber()) // go to right
            thisNode = thisNode->right;
        else // found
            return thisNode;
    }
}

/*Recursive function to do inorder traversal of subtrees within the range*/
void getRangeSubtree(RBNode* RBTreeRoot, int rideNumber1, int rideNumber2, std::vector<Ride*>& rangeRides) {
    /* append all elements in [rideNumber1, rideNumber2] in the subtree rooted at root to rangeRides */
    if (RBTreeRoot == nullptr) {
        return;
    }
    // Left subtree search
    if (rideNumber1 < RBTreeRoot->getRide()->getRideNumber()) {
        getRangeSubtree(RBTreeRoot->left, rideNumber1, rideNumber2, rangeRides);
    }
    // output root
    if (rideNumber1 <= RBTreeRoot->getRide()->getRideNumber()
        && rideNumber2 >= RBTreeRoot->getRide()->getRideNumber()) {
        rangeRides.push_back(RBTreeRoot->getRide());
    }
    // search right subtree
    if (rideNumber2 > RBTreeRoot->getRide()->getRideNumber()) {
        getRangeSubtree(RBTreeRoot->right, rideNumber1, rideNumber2, rangeRides);
    }
}

// Range function -> to print values in a range
std::vector<Ride*> RBTree::getRidesInRangeFromRBTree(int rideNumber1, int rideNumber2) {
    std::vector<Ride*> rangeRides;
    getRangeSubtree(RBTreeRoot, rideNumber1, rideNumber2, rangeRides);
    if (rangeRides.size() == 0)
        rangeRides.push_back(nullRide);
    return rangeRides;
}

int BSTInsert(RBNode*& RBTreeRoot, RBNode* newNode) {

    if (RBTreeRoot == nullptr) {
        RBTreeRoot = newNode;
        return 1;
    }
    // Duplicate record case
    if (newNode->getRide()->getRideNumber() == RBTreeRoot->getRide()->getRideNumber())
    {
        return 0;
        //throw new std::invalid_argument("The inserted ride has a duplicate rideNumber: " + std::to_string(newNode->getRide()->getRideNumber()));
    }
    newNode->parent = RBTreeRoot;
    if (newNode->getRide()->getRideNumber() < RBTreeRoot->getRide()->getRideNumber()) // insert to left
        BSTInsert(RBTreeRoot->left, newNode);
    if (newNode->getRide()->getRideNumber() > RBTreeRoot->getRide()->getRideNumber()) // insert to right
        BSTInsert(RBTreeRoot->right, newNode);

}

/*Insert / Delete Utility functions. Helps in performing rotations and color changes*/
RBNode* removeDegree1(RBNode* toremove, RBNode* toraise, RBTree* tree) {
    RBNode* v;
    if (toremove->parent != nullptr) { // toremove is not root
        if (toremove->parent->left == toremove) {
            toremove->parent->left = toraise;
            v = toremove->parent->right;
        }
        else {
            toremove->parent->right = toraise;
            v = toremove->parent->left;
        }
    }
    else {
        tree->RBTreeRoot = toraise; // toremove is root
        v = nullptr;
    }
    if (toraise != nullptr) {
        toraise->parent = toremove->parent;
        toraise->color = BLACK;
    }
    return v;
}
void raiseup(RBNode* toraise, RBNode* gp, RBTree* tree) {
    /* put toraise to gp's position */
    RBNode* sib = removeDegree1(gp, toraise, tree);
    gp->parent = toraise;
    gp->color = RED;
}

void LLb_rotation(RBNode* pp, RBNode* gp, RBTree* tree) {
    raiseup(pp, gp, tree);
    RBNode* c = pp->right;
    gp->left = c;
    pp->right = gp;
    if (c != nullptr) c->parent = gp;
}
void RRb_rotation(RBNode* pp, RBNode* gp, RBTree* tree) {
    raiseup(pp, gp, tree);
    RBNode* c = pp->left;
    gp->right = c;
    pp->left = gp;
    if (c != nullptr) c->parent = gp;
}
void LRb_rotation(RBNode* p, RBNode* pp, RBNode* gp, RBTree* tree) {
    raiseup(p, gp, tree);
    pp->parent = p;
    RBNode* b = p->left;
    RBNode* c = p->right;
    pp->right = b;
    gp->left = c;
    p->left = pp;
    p->right = gp;
    if (b != nullptr) b->parent = pp;
    if (c != nullptr) c->parent = gp;
}
void RLb_rotation(RBNode* p, RBNode* pp, RBNode* gp, RBTree* tree) {
    raiseup(p, gp, tree);
    pp->parent = p;
    RBNode* b = p->right;
    RBNode* c = p->left;
    pp->left = b;
    gp->right = c;
    p->right = pp;
    p->left = gp;
    if (b != nullptr) b->parent = pp;
    if (c != nullptr) c->parent = gp;
}

void twoRedRotation(RBNode* p, RBNode* pp, RBNode* gp, RBTree* tree) {
    if (pp == gp->left && p == pp->left) LLb_rotation(pp, gp, tree);
    if (pp == gp->right && p == pp->right) RRb_rotation(pp, gp, tree);
    if (pp == gp->left && p == pp->right) LRb_rotation(p, pp, gp, tree);
    if (pp == gp->right && p == pp->left) RLb_rotation(p, pp, gp, tree);
}

void adjustTwoRed(RBNode* p, RBTree* tree) {
    /* adjust if p and pp are both red */
    RBNode* pp = p->parent;
    if (pp == nullptr) { // p is root
        p->color = BLACK;
        return;
    }
    RBNode* gp = pp->parent;
    if (gp == nullptr) { // pp is root
        pp->color = BLACK;
        return;
    }
    if (p->color == RED && pp->color == RED) {
        if (pp->getSibling() != nullptr) {
            if (pp->getSibling()->color == RED) { // color flip
                pp->color = BLACK;
                gp->color = RED;
                pp->getSibling()->color = BLACK;
                adjustTwoRed(gp, tree);
            }
            else twoRedRotation(p, pp, gp, tree);
        }
        else twoRedRotation(p, pp, gp, tree);
    }
}

/*Called when we insert a Ride in RBTree*/
int RBTree::insertRideInRBTree(Ride* toInsert) {
    RBNode* newNode = new RBNode(toInsert);
    int res = BSTInsert(RBTreeRoot, newNode);
    if (res == 0) {
        return 0;
    }
    adjustTwoRed(newNode, this);
    return 1;
}

    /* Called as part of the remove operation to 
    adjust if py is the parent of a deficient node
     * v is the sibling of the deficient node */
void adjustDeficient(RBNode* py, RBNode* v, RBTree* tree) {

    if (py == nullptr)
        return; // y is root
    RBNode* w, * a, * b, * c, * x;
    int pycolor = py->getColor();
    bool Rxx = (v == py->left); // 1 for RXx, 0 for LXx
    w = Rxx ? v->right : v->left;
    if (v->color == BLACK) {
        a = Rxx ? v->left : v->right;
        if (w != nullptr && w->color == RED) { // Lb2, Rb2 or Lb1, Rb1 case 2
            if (Rxx) LRb_rotation(w, v, py, tree);
            else RLb_rotation(w, v, py, tree);
            w->color = pycolor;
            py->color = BLACK;
            return;
        }
        else {
            if (a != nullptr && a->color == RED) { // Lb1, Rb1 case 1
                if (Rxx) LLb_rotation(v, py, tree);
                else RRb_rotation(v, py, tree);
                v->color = pycolor;
                py->color = BLACK;
                a->color = BLACK;
                return;
            }
            else { // Lb0, Rb0
                if (pycolor == BLACK) { // Lb0, Rb0 case 1
                    v->color = RED;
                    if (py->parent == nullptr) return;
                    else adjustDeficient(py->parent, py->getSibling(), tree);
                }
                else { // Lb0, Rb0 case 2
                    v->color = RED;
                    py->color = BLACK;
                    return;
                }
            }
        }
    }
    else { // v red
        a = Rxx ? w->left : w->right;
        x = Rxx ? w->right : w->left;
        if (x != nullptr && x->color == RED) { // Lr(2), Rr(2) or Lr(1), Rr(1) case 2
            if (Rxx) LRb_rotation(x, v, py, tree);
            else RLb_rotation(x, v, py, tree);
            if (Rxx) {
                w->right = v->right;
                if (v->right != nullptr) v->right->parent = w;
                v->right = w;
            }
            else {
                w->left = v->left;
                if (v->left != nullptr) v->left->parent = w;
                v->left = w;
            }
            w->parent = v;
            py->color = BLACK;
            return;
        }
        else {
            if (a != nullptr && a->color == RED) { // Lr(1), Rr(1) case 1
                if (Rxx) LRb_rotation(w, v, py, tree);
                else RLb_rotation(w, v, py, tree);
                py->color = BLACK;
                a->color = BLACK;
                return;
            }
            else { // Lr(0), Rr(0)
                if (Rxx) LLb_rotation(v, py, tree);
                else RRb_rotation(v, py, tree);
                py->color = BLACK;
                w->color = RED;
                return;
            }
        }

    }
}

/* Method to find the rightmost leaf in the left subtree and replace
 * assuming toreplace has both left and right child
 * return the leaf node */
RBNode* replace(RBNode* toreplace) {

    RBNode* thisNode = toreplace->left;
    while (1) {
        if (thisNode->right == nullptr) { // swap thisNode and toreplace
            // plan A
            std::swap(toreplace->ride, thisNode->ride);
            return thisNode;
        }
        else thisNode = thisNode->right;
    }
}

/*Remove Ride from the RBTree*/
void RBTree::removeRideFromRBTree(int rideNumber) {
    RBNode* removenode = get(rideNumber);
    RBNode* toraise = nullptr;
    bool adjust = false; // whether need to continue adjusting
    if ((removenode->left == nullptr) ^ (removenode->right == nullptr)) { // degree 1 node
        if (removenode->left != nullptr) toraise = removenode->left; // degree 1 node with left child
        else if (removenode->right != nullptr) toraise = removenode->right; // degree 1 node with right child
    }
    else { // leaf or degree 2
        if (removenode->left != nullptr) removenode = replace(removenode); // degree 2 node
        toraise = removenode->left; // can be null
    }
    if (removenode->color == BLACK) { // might neet to rebalance
        if (toraise == nullptr) adjust = true;
        else if (toraise->color == BLACK) adjust = true;
    }
    RBNode* v = removeDegree1(removenode, toraise, this);
    if (adjust) adjustDeficient(removenode->parent, v, this);
}