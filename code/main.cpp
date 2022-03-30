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
void testReadEnv(Env env);

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();
    reachablePositions->printNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution);

    delete pathplanner;
    delete reachablePositions;
    delete solution;

}

void readEnvStdin(Env env){
    // read input as char for each env location
    // EOF when max size is exceeded

    int size = 0;
    while(!std::cin.eof() && size < (ENV_DIM * ENV_DIM)){
        for(int row = 0; row < ENV_DIM; ++row) {
            for(int col = 0; col < ENV_DIM; ++col) {
                std::cin >> env[row][col];
                ++size;
            }
        }
    }
}

void printPath(Env env, NodeList* solution) {
    //TODO
}

void printReachablePositions(Env env, NodeList* reachablePositions){
    //TODO
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

void testReadEnv(Env env) {
    // Print out env input for test

    std::cout << "\n\nstandard print of env:\n" << std::endl;
    for(int i = 0; i < ENV_DIM; ++i) {
            for(int j = 0; j < ENV_DIM; ++j) {
                std::cout << env[i][j];
            }
            std::cout << "\n";
        }
    std::cout << "\n";
}