
#include "NodeList.h"
#include <iostream>



NodeList::NodeList() : 
   length(0) 
{}


NodeList::~NodeList(){
   
}

NodeList::NodeList(NodeList& other){
    // TODO
}


int NodeList::getLength(){
   return length;
}


NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   nodes[length] = newNode;
   ++length;
}

bool NodeList::containsNode(NodePtr node){
   for(int i = 0; i < length; ++i){
      if(node->getRow() == nodes[i]->getRow() && node->getCol() == nodes[i]->getCol()) {
            return true;
         }
   }
   return false;
}

void NodeList::clear(){
   for(int i = length - 1; i >=0; --i){
      delete nodes[i];
      --length;
   }
}

void NodeList::printNodes(){
   for(int i = 0; i < length; ++i) {
      std::cout << nodes[i]->getRow() << "," << nodes[i]->getCol() << "," << nodes[i]->getDistanceToS() << std::endl;
   }
}

