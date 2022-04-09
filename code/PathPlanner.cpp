
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols) {
   // Copy env to global env
   for(int row = 0; row < rows; ++row){
      for(int col = 0; col < cols; ++col){     
         envCopy[row][col] = env[row][col];
      }
   }
   // Create first Node as initial position
   for(int row = 0; row < rows; ++row){
      for(int col = 0; col < cols; ++col){     
         if(envCopy[row][col] == SYMBOL_START){
            initialPosition(row, col);
         }
      }
   }
}

PathPlanner::~PathPlanner(){
   delete openList;
   delete closedList;
}

void PathPlanner::initialPosition(int row, int col){
   // Immediately adds initial position to the open list
   S = new Node(row, col, 0);
   openList = new NodeList();
   openList->addBack(S);
   delete S;
}

NodeList* PathPlanner::getReachableNodes(){
   Node* p = new Node(*openList->get(0));
   Node* q;
   closedList = new NodeList();

   // Add p to closed list until open list is exhausted
   while(openList->getLength() != closedList->getLength()) {
      int row = p->getRow();
      int col = p->getCol();
      int dis = p->getDistanceToS();
      
      // Check up and add to openList if an available path 
      if(row > 0) {
         if((envCopy[row - 1][col] == SYMBOL_EMPTY || envCopy[row - 1][col] == SYMBOL_GOAL)) {
            q = new Node(row - 1, col, dis + 1);
            if(!openList->containsNode(q)) {
               openList->addBack(q);
            }
            delete q;
         }
      }
      // Check right and add to openList if an available path 
      if(envCopy[row][col + 1] == SYMBOL_EMPTY || envCopy[row][col + 1] == SYMBOL_GOAL) {
         q = new Node(row, col + 1, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
         delete q;
      }
      // Check down and add to openList if an available path 
      if(envCopy[row + 1][col] == SYMBOL_EMPTY || envCopy[row + 1][col] == SYMBOL_GOAL) {
         q = new Node(row + 1, col, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
         delete q;
      }
      // Check left and add to openList if an available path
      if(col > 0) { 
         if((envCopy[row][col - 1] == SYMBOL_EMPTY || envCopy[row][col - 1] == SYMBOL_GOAL)) {
            q = new Node(row, col - 1, dis + 1);
            if(!openList->containsNode(q)) {
               openList->addBack(q);
            }
            delete q;
      }
      }

      // Add p to closed list
      closedList->addBack(p);
      delete p;
      // Select new p from openList not in closedList
      for(int i = openList->getLength() - 1; i >= 0; --i) {
         if(!(closedList->containsNode(openList->get(i)))) {
            p = new Node(*openList->get(i));
         }
      }

   }
   // Return deep copy of closed list
   return new NodeList(*closedList);
}

NodeList* PathPlanner::getPath(){
   // Get Node for goal position
   Node* p = new Node(0, 0, 0);
   for(int i = 0; i < closedList->getLength(); ++i) {
      if(envCopy[closedList->get(i)->getRow()][closedList->get(i)->getCol()] == SYMBOL_GOAL) {
         delete p;
         p = new Node(*closedList->get(i));
      }
   }
   // Create path node list and add goal position
   NodeList* path = new NodeList();
   path->addBack(p);

   // Add available neighbours to a list
   openList->clear();
   Node* q;
   while(p->getDistanceToS() != 0) {
      for(int i = closedList->getLength() - 1; i >= 0; --i) {
         q = new Node(*closedList->get(i));
         // Check up
         if(q->getRow() == p->getRow() - 1 && q->getCol() == p ->getCol()) {
            openList->addBack(q);
         } // Check right
         if(q->getRow() == p->getRow() && q->getCol() == p ->getCol() + 1) {
            openList->addBack(q);
         } // Check down
         if(q->getRow() == p->getRow() + 1 && q->getCol() == p ->getCol()) {
            openList->addBack(q);
         } // Check left
         if(q->getRow() == p->getRow() && q->getCol() == p ->getCol() - 1) {
            openList->addBack(q);
         }
         delete q;
      } // Point p to Node in openList with lowest distance to S
      for(int i = 0; i < openList->getLength(); ++i) {
         if(openList->get(i)->getDistanceToS() < p->getDistanceToS()){
            p = openList->get(i);
         }
      } // Add p to solution path if not already added
      if(!path->containsNode(p)){
            path->addBack(p);
      }
   }

   // Return a deep copy of the path
   return new NodeList(*path);
}
