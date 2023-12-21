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

bool SpaceSectorLLRBT::isRed(Sector* node) {
    return node->color == RED;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* node) {
    Sector* child = node->right;
    node->right = child->left;
    child->left = node;
    child->color = node->color;
    node->color = RED;
    return child;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* node) {
    Sector* child = node->left;
    node->left = child->right;
    child->right = node;
    child->color = node->color;
    node->color = RED;
    return child;
}

void SpaceSectorLLRBT::flip(Sector* node) {
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

Sector* SpaceSectorLLRBT::insert(Sector* node, int x, int y, int z) {
    if (node == nullptr) {
        Sector* new_sector = new Sector(x, y, z);
        new_sector->sector_code = getSectorCode(x, y, z);
        new_sector->color = RED; // New nodes are always inserted as RED
        return new_sector;
    }

    if (x < node->x || (x == node->x && y < node->y) || (x == node->x && y == node->y && z < node->z)) {
        node->left = insert(node->left, x, y, z);

    } else {
        node->right = insert(node->right, x, y, z);
    }

    // Fix up any right-leaning links
    if (isRed(node->right) && !isRed(node->left)) {
        cout << "first if in" << endl;
        node = rotateLeft(node);
        cout << "first if out" << endl;
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        cout << "second if in" << endl;
        node = rotateRight(node);
        cout << "second if out" << endl;
    }
    if (isRed(node->left) && isRed(node->right)) {
        cout << "third if in" << endl;
        flip(node);
        cout << "third if out" << endl;
    }

    return node;
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.

    std::string sector_code = getSectorCode(x, y, z);

    Sector* new_sector = new Sector(x, y, z);
    new_sector->sector_code = sector_code;

    sectorMap[sector_code] = std::make_tuple(x, y, z);

    if (root == nullptr) {
        root = new_sector;
        root->color = BLACK; // Root is always BLACK
    } 
    else {
        root = insert(root, x, y, z);
        cout << "post insert" << endl;
        root->color = BLACK; // Root is always BLACK
        cout << "colored black" << endl;
    }
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

Sector* SpaceSectorLLRBT::pathGetter(Sector* root, int x, int y, int z) {
    if (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z < root->z)) {
        return root->left;
    }
    else {
        return root->right;
    }
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!

    auto final_sector = sectorMap.find(sector_code);

    if (final_sector == sectorMap.end()) {
        cout << "A path to Dr. Elara could not be found." << endl;
        return std::vector<Sector*>();
    }

    int x, y, z;
    std::tie(x, y, z) = final_sector->second;

    while ((root->x != x) || (root->y != y) || (root->z != z)) {
        path.push_back(root);
        root = pathGetter(root, x, y, z);
    }

    path.push_back(root);

    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.

    if (!path.empty()) {
        cout << "The stellar path to Dr. Elara: " << path[0]->sector_code;
        
        for (int i = 1; i < path.size(); i++) {
            cout << "->" << path[i]->sector_code;
        }

        cout << endl;
    }
}