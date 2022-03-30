
#include "Node.h"


Node::Node(int row, int col, int distanceToS) :
   row(row), col(col), distanceToS(distanceToS)
{}
    
Node::~Node(){

}

int Node::getRow(){
   return row;
}

int Node::getCol(){
   return col;
}

int Node::getDistanceToS(){
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS){
   this->distanceToS = distanceToS;
}
