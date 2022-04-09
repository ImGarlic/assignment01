
#include "NodeList.h"
#include <iostream>



NodeList::NodeList() : length(0){
}


NodeList::~NodeList(){
   this->clear();
}

NodeList::NodeList(NodeList& other) : length(other.length){
   // Copy all nodes
   for(int i = 0; i < length; ++i) {
      nodes[i] = new Node(*other.nodes[i]);
   }
}


int NodeList::getLength(){
   return length;
}

NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   // Add newNode to the end of the NodeList
   nodes[length] = new Node(*newNode);
   ++length;
}

bool NodeList::containsNode(NodePtr node){
   // Check if NodeList contains node, distance not required
   for(int i = 0; i < length; ++i){
      if(node->getRow() == nodes[i]->getRow() && node->getCol() == nodes[i]->getCol()) {
            return true;
         }
   }
   return false;
}

void NodeList::clear(){
   // Delete nodes in reverse order
   int num = length;
   for(int i = 0; i < num; ++ i) {
      if(nodes[i] != nullptr) {
         delete nodes[i];
         --length;
      }
   }
}

void NodeList::printNodes(){
   // Testing function to print all nodes in NodeList
   for(int i = 0; i < length; ++i) {
      std::cout << nodes[i]->getRow() << "," << nodes[i]->getCol() << "," << nodes[i]->getDistanceToS() << std::endl;
   }
   std::cout << "List length: " << length << std::endl;
}

