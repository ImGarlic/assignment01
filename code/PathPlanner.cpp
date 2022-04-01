
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols) {
      // Copy env input to private Env
      for(int row = 0; row < rows; ++row) {
         for(int col = 0; col < cols; ++col) {
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
   
}

void PathPlanner::initialPosition(int row, int col){
   // Immediately adds initial pos to the open list
   S = new Node(row, col, 0);
   openList = new NodeList();
   openList->addBack(S);
}

NodeList* PathPlanner::getReachableNodes(){
   Node* p = openList->get(0);
   Node* q = new Node(0, 0, 0);
   closedList = new NodeList();

   // Add p to closed list until open list is exhausted
   while(openList->getLength() != closedList->getLength()) {
      int row = p->getRow();
      int col = p->getCol();
      int dis = p->getDistanceToS();
      
      // Check up and add to openList if an available path 
      if(envCopy[row - 1][col] == SYMBOL_EMPTY || envCopy[row - 1][col] == SYMBOL_GOAL) {
         q = new Node(row - 1, col, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
      }
      // Check right and add to openList if an available path 
      if(envCopy[row][col + 1] == SYMBOL_EMPTY || envCopy[row][col + 1] == SYMBOL_GOAL) {
         q = new Node(row, col + 1, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
      }
      // Check down and add to openList if an available path 
      if(envCopy[row + 1][col] == SYMBOL_EMPTY || envCopy[row + 1][col] == SYMBOL_GOAL) {
         q = new Node(row + 1, col, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
      }
      // Check left and add to openList if an available path 
      if(envCopy[row][col - 1] == SYMBOL_EMPTY || envCopy[row][col - 1] == SYMBOL_GOAL) {
         q = new Node(row, col - 1, dis + 1);
         if(!openList->containsNode(q)) {
            openList->addBack(q);
         }
      }

      // Add p to closed list
      closedList->addBack(p);
      // Select new p from openList not in closedList
      for(int i = 0; i < openList->getLength(); ++i) {
         if(!closedList->containsNode(openList->get(i))) {
            p = openList->get(i);
         }
      }

   }
   // Return deep copy of list
   closedList = new NodeList(*closedList);
   openList->clear();
   return closedList;
}

NodeList* PathPlanner::getPath(){
   // Get Node for goal position
   Node* p = new Node(0, 0, 0);
   for(int i = 0; i < closedList->getLength(); ++i) {
      if(envCopy[closedList->get(i)->getRow()][closedList->get(i)->getCol()] == SYMBOL_GOAL) {
         p = new Node(*closedList->get(i));
         break;
      }
   }
   // Create path node list and add goal position
   NodeList* path = new NodeList();
   path->addBack(p);

   // Create a list to add the cardinal directions around p
   NodeList* openList = new NodeList();
   Node* q;
   while(p->getDistanceToS() != 0) {
      for(int i = closedList->getLength() - 1; i >= 0; --i) {
         // 
         q = closedList->get(i);
         if(q->getRow() == p->getRow() - 1 && q->getCol() == p ->getCol()) {
            openList->addBack(q);
         }
         if(q->getRow() == p->getRow() && q->getCol() == p ->getCol() + 1) {
            openList->addBack(q);
         }
         if(q->getRow() == p->getRow() + 1 && q->getCol() == p ->getCol()) {
            openList->addBack(q);
         }
         if(q->getRow() == p->getRow() && q->getCol() == p ->getCol() - 1) {
            openList->addBack(q);
         }
      }
      for(int i = 0; i < openList->getLength(); ++i) {
         if(openList->get(i)->getDistanceToS() < p->getDistanceToS()){
            p = openList->get(i);
         }
      }
      if(!path->containsNode(p)){
            path->addBack(p);
      }
   }

   NodeList* copyPath = new NodeList(*path);
   copyPath->printNodes();
   delete p;
   delete path;
   return copyPath;
}
