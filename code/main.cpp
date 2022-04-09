//   This implementation only includes up to milestone 3. While I did attempt milestone 4; I ran into way too many issues 
//   that I just couldn't get around.

//   My implementation of this program was centred around the psuedo code provided to us in the assignment spec.
//   The idea was to ensure that NodeLists were working perfectly before applying them to the pathplanner algorithms.
//   The way this program works is by adding chars directly to the environment via std::cin. The getReachableNodes algorithm
//   then finds the "S" start point and adds any "." empty position - in order of distance from the start point - to the NodeList 
//   of reachablePositions. From there the getPath function can reverse search from the "G" goal position, finding available nodes
//   with the shortest distanceToS. Thus, when printing, I had to ensure that the direction symbols were the reverse of the 
//   direction the nodes were added.
//   The biggest issue I ran into was that I could not find a reasonable method to set a private Env without copying
//   the input in the constructor. For some reason I could not just declare the private Env to be the same when the ENV_DIM was
//   defined. This changed when I tried to implement milestone 4. I am very confused.


// Start code
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"


// Read an environment from standard input
void readEnvStdin(Env env, int rows, int cols);

// Print out current environment
void printEnv(Env env, int rows, int cols);

// Intergrates solution path into environment, then calls printEnv()
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
    // i is set to not include start and goal positions
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
    printEnv(env, ENV_DIM, ENV_DIM);
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

void printEnv(Env env, int rows, int cols) {
    // Print out env input for test

    std::cout << "\nSolution:\n" << std::endl;
    for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                std::cout << env[i][j];
            }
            std::cout << "\n";
        }
}