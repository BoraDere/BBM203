#include "SpaceSectorLLRBT.h"
#include <cmath>

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
    std::ifstream infile(filename);
    std::string line;

    int x, y, z;
    char comma = ',';
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
    
        if (!(iss >> x >> comma >> y >> comma >> z)) {continue;} // first line

        iss >> x >> comma >> y >> comma >> z;

        insertSectorByCoordinates(x, y, z);
    }
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
}

std::string SpaceSectorLLRBT::getSectorCode(int x, int y, int z) {

    std::string sector_code;

    int distance = std::sqrt(x*x + y*y + z*z);
    sector_code += std::to_string(distance);

    sector_code += (x == 0 ? 'S' : (x > 0 ? 'R' : 'L'));
    sector_code += (y == 0 ? 'S' : (y > 0 ? 'U' : 'D'));
    sector_code += (z == 0 ? 'S' : (z > 0 ? 'F' : 'B'));

    return sector_code;
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

void SpaceSectorLLRBT::displaySectorsInOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    displaySectorsInOrderHelper(node->left);
    std::cout << node->sector_code << std::endl;
    displaySectorsInOrderHelper(node->right);
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
    cout << "Space sectors inorder traversal:" << endl;
    displaySectorsInOrderHelper(root);
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPreOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->sector_code << std::endl;
    displaySectorsPreOrderHelper(node->left);
    displaySectorsPreOrderHelper(node->right);
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors preorder traversal:" << endl;
    displaySectorsPreOrderHelper(root);
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    displaySectorsPostOrderHelper(node->left);
    displaySectorsPostOrderHelper(node->right);
    std::cout << node->sector_code << std::endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    displaySectorsPostOrderHelper(root);
    cout << endl;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}