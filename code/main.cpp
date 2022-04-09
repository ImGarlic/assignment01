#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();
void testReadEnv(Env env, int rows, int cols);


// Read an environment from standard input
void readEnvStdin(Env env, int rows, int cols);

// Print out a Environment to standard output with path.
void printPath(Env env, NodeList* solution);

// Print a list of the reachable positions and the list length
// This includes the Start and Goal positions
void printReachablePositions(NodeList* reachablePositions);


int main(int argc, char** argv){

    // Load environment
    Env env;
    int rows = ENV_DIM;
    int cols = ENV_DIM;

    // Read environment to the Env array
    readEnvStdin(env, rows, cols);
    
    // Solve using forwardSearch
    PathPlanner* pathplanner = new PathPlanner(env, rows, cols);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution);
    
    // Cleanup
    delete pathplanner;
    delete reachablePositions;
    delete solution;

}

void readEnvStdin(Env env, int rows, int cols){
    while(!std::cin.eof()){
        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                std::cin >> env[row][col];
        }
    }
    }
}

void printPath(Env env, NodeList* solution) {
    Node* p = new Node(*solution->get(0));
    Node* q;
    for(int i = 1; i < solution->getLength() - 1; ++i) {
        q = solution->get(i);
        int row = q->getRow();
        int col = q->getCol();
        if(row == (p->getRow() - 1)) { // Check Up
            env[row][col] = 'V';
        }
        if(col == (p->getCol() + 1)) { // Check Right
            env[row][col] = '<';
        }
        if(row == (p->getRow() + 1)) { // Check Down
            env[row][col] = '^';
        }
        if(col == (p->getCol() - 1)) { // Check Left
            env[row][col] = '>';
        }
        p = q;
    }
    int rows = ENV_DIM;
    int cols = ENV_DIM;
    testReadEnv(env, rows, cols);
}

void printReachablePositions(NodeList* reachablePositions) {
    for(int i = 0; i < reachablePositions->getLength(); ++i) {
        Node* node = new Node(*reachablePositions->get(i));
        std::cout << node->getRow() << ",";
        std::cout << node->getCol() << ",";
        std::cout << node->getDistanceToS() << std::endl;
        delete node;
    }
    std::cout << "Number reachable: " << reachablePositions->getLength() << std::endl;
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;

    // Check if a Node is in NodeList - 1 is true, 0 is false
    std::cout << nodeList->containsNode(b2) << std::endl;
    Node* b3 = new Node (2, 2, 2);
    std::cout << nodeList->containsNode(b3) << std::endl;

    // CLear list
    nodeList->clear();
    std::cout << "Cleared list\n";
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
}

void testReadEnv(Env env, int rows, int cols) {
    // Print out env input for test

    std::cout << "\n\nSolution:\n" << std::endl;
    for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                std::cout << env[i][j];
            }
            std::cout << "\n";
        }
}