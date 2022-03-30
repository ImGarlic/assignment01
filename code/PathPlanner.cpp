
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols) {
      // Cope 
      for(int row = 0; row < rows; ++row) {
         for(int col = 0; col < cols; ++col) {
            envCopy[row][col] = env[row][col];         
            }
      }
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
   S = new Node(row, col, 0);
   openList = new NodeList();
   openList->addBack(S);
}

NodeList* PathPlanner::getReachableNodes(){
   Node* p = openList->get(0);
   Node* q;
   closedList = new NodeList();

   while(openList->getLength() != closedList->getLength()) {
      for(int i = 0; i < 4; ++i) {
         if(i == 0) { // Up
            q = new Node(p->getRow() - 1, p->getCol(), p->getDistanceToS() + 1);
         }
         if(i == 1) { // Right
            q = new Node(p->getRow(), p->getCol() + 1, p->getDistanceToS() + 1);
         }
         if(i == 2) { // Down
            q = new Node(p->getRow() + 1, p->getCol(), p->getDistanceToS() + 1);
         }
         if(i == 3) { // Left
            q = new Node(p->getRow(), p->getCol() - 1, p->getDistanceToS() + 1);
         }
         if(envCopy[q->getRow()][q->getCol()] == SYMBOL_EMPTY && !openList->containsNode(q)) {
            openList->addBack(q);
         }
      }

      closedList->addBack(p);
      for(int i = 0; i < openList->getLength(); ++i) {
         if(!closedList->containsNode(openList->get(i))) {
            p = openList->get(i);
         }
      }

   }
   
   return closedList;
}

NodeList* PathPlanner::getPath(){
   return nullptr;
}
