#include "pairingHeap.h"
#include "error.h"
using namespace::std;

PairingHeap::PairingHeap(){
    logicalSize = 0;
    origin = NULL;
}

PairingHeap::~PairingHeap(){
    deleteAll(origin);
}

void PairingHeap::deleteAll(PairNode *node){
    if (node->leftChild != NULL) deleteAll(node->leftChild);
    if (node->sibling   != NULL) deleteAll(node->sibling);
    delete node;
}

void PairingHeap::insert(string name, int value){
    PairNode *node = new PairNode(name, value, NULL, NULL);
    logicalSize++;
    if (origin == NULL){
        origin = node;
    } else {
        origin = mergeTrees(origin, node);
    }
}

bool PairingHeap::isEmpty() const{
    return logicalSize == 0;
}


PairNode *PairingHeap::mergeTrees(PairNode *first, PairNode *second){
//    if (first->value == NULL) return second;
//    if (second->value == NULL) return first;
    if (first->value <= second->value){
        first->addChild(second);
        return first;
    } else {
        second->addChild(first);
        return second;
    }
}

PairNode PairingHeap::peek() const{
    if (origin == NULL){
        error("Tree is empty");
    } else {
        return *origin;
    }
}

void PairingHeap::printOut() const{
    for (PairNode *node = origin; node != NULL;node = node->leftChild){
        cout << node->name << ":" << node->value << endl;
    }
}

PairNode *PairingHeap::remove(){
    logicalSize--;
    PairNode *topValue = origin;
    origin = mergeSiblings(origin->leftChild);
    return topValue;
}

// use after deleting origin
PairNode *PairingHeap::mergeSiblings(PairNode *node){
    if (node == NULL || node->sibling == NULL) {
        return node;
    } else {
        PairNode *first, *second, *newNode;
        first = node;
        second = node->leftChild;
        newNode = node->leftChild->leftChild;
        return mergeTrees(first, second), mergeSiblings(newNode);
    }
}


