#include "SpaceSectorLLRBT.h"
#include <cmath>

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
    std::ifstream file(filename);
    std::string line;

    int x, y, z;
    char comma = ',';
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
    
        if (!(iss >> x >> comma >> y >> comma >> z)) {continue;} // first line

        iss >> x >> comma >> y >> comma >> z;

        insertSectorByCoordinates(x, y, z);
    }
}

void SpaceSectorLLRBT::deleteTree(Sector* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    //cout << "SpaceSectorLLRBT destructor called" << endl;
    deleteTree(root);
}

bool SpaceSectorLLRBT::isRed(Sector* node) {
    if (!node) {
        return false; // Null nodes are BLACK
    }
    return node->color == RED;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* node) {
    Sector* child = node->right;
    node->right = child->left;
    if (child->left != nullptr) {
        child->left->parent = node;
    }
    child->left = node;
    child->color = node->color;
    node->color = RED;
    child->parent = node->parent;
    node->parent = child;
    return child;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* node) {
    Sector* child = node->left;
    node->left = child->right;
    if (child->right != nullptr) {
        child->right->parent = node;
    }
    child->right = node;
    child->color = node->color;
    node->color = RED;
    child->parent = node->parent;
    node->parent = child;
    return child;
}

void SpaceSectorLLRBT::flip(Sector* node) {
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
    if (node->left != nullptr) {
        node->left->parent = node;
    }
    if (node->right != nullptr) {
        node->right->parent = node;
    }
}

Sector* SpaceSectorLLRBT::insert(Sector* node, int x, int y, int z) {
    if (node == nullptr) {
        Sector* new_sector = new Sector(x, y, z); 
        new_sector->color = RED; // New nodes are always inserted as RED
        return new_sector;
    }

    if (x < node->x || (x == node->x && y < node->y) || (x == node->x && y == node->y && z < node->z)) {
        node->left = insert(node->left, x, y, z);
        node->left->parent = node;
    } else {
        node->right = insert(node->right, x, y, z);
        node->right->parent = node;
    }

    // Fix up any right-leaning links
    if (isRed(node->right) && !isRed(node->left)) {
        node = rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        node = rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right)) {
        flip(node);
    }

    return node;
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.

    Sector* new_sector = new Sector(x, y, z);

    sectorMap[new_sector->sector_code] = std::make_tuple(x, y, z);

    if (root == nullptr) {
        root = new_sector;
        root->color = BLACK; // Root is always BLACK
        root->parent = nullptr;
    } 
    else {
        root = insert(root, x, y, z);
        root->color = BLACK; // Root is always BLACK
    }
}

void SpaceSectorLLRBT::displaySectorsInOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    displaySectorsInOrderHelper(node->left);
    std::string color = node->color ? "RED" : "BLACK";
    std::cout << color << " sector: " << node->sector_code << std::endl;
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

    std::string color = node->color ? "RED" : "BLACK";
    std::cout << color << " sector: " << node->sector_code << std::endl;
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
    std::string color = node->color ? "RED" : "BLACK";
    std::cout << color << " sector: " << node->sector_code << std::endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    displaySectorsPostOrderHelper(root);
    cout << endl;
}

Sector* SpaceSectorLLRBT::pathGetter(Sector* root, int x, int y, int z) {
    if (!root) {
        return nullptr;
    }

    return (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z < root->z)) ? root->left : root->right;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!

    auto final_sector = sectorMap.find(sector_code);

    if (final_sector == sectorMap.end()) { // no path -- THE SAME WITH THE BST ONE
        cout << "A path to Dr. Elara could not be found." << endl;
        return std::vector<Sector*>();
    }

    int x, y, z;
    std::tie(x, y, z) = final_sector->second;

    while (root && ((root->x != x) || (root->y != y) || (root->z != z))) {
        path.push_back(root);
        root = pathGetter(root, x, y, z);
    }

    if (root) {
        path.push_back(root);
    }

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