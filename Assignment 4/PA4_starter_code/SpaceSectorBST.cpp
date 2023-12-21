#include "SpaceSectorBST.h"
#include <cmath>

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
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

std::string SpaceSectorBST::getSectorCode(int x, int y, int z) {

    std::string sector_code;

    int distance = std::sqrt(x*x + y*y + z*z);
    sector_code += std::to_string(distance);

    sector_code += (x == 0 ? 'S' : (x > 0 ? 'R' : 'L'));
    sector_code += (y == 0 ? 'S' : (y > 0 ? 'U' : 'D'));
    sector_code += (z == 0 ? 'S' : (z > 0 ? 'F' : 'B'));

    return sector_code;
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
    // coordinates-based comparison criteria is first x, then y, then z
    // this is a recursive function
    // if the root is null, then the new sector is the root
    // if the root is not null, then compare the new sector to the root
    // if the new sector is less than the root, then insert the new sector to the left of the root
    // if the new sector is greater than or equal to the root, then insert the new sector to the right of the root
    // this recursive function will:
    // Take the current node and its coordinates as parameters
    /* Begin the insertion with the root node of the BST. If the BST is empty (root is nullptr), the
    new node becomes the root. Otherwise, compare the coordinates as explained above. If the sorting
    criteria require inserting the sector to the left, proceed to the left child. Otherwise, proceed to the
    right child.*/
    /* Recursive Call: Make a recursive call to the insert function with the left or right child based on the
    comparison. If the child is nullptr, create a new node with the given distance and attach it at
    this position.*/
    /* Return the current node after each recursive call to maintain the tree structure. This ensures that
    the root of the subtree (or the overall tree) is updated correctly after the insertion.*/
    /* The node returned from the initial call of the function (starting at the root) is assigned as the new
    root of the BST.*/

    std::string sector_code = getSectorCode(x, y, z);

    Sector* new_sector = new Sector(x, y, z);
    new_sector->sector_code = sector_code;

    if (root == nullptr) {
        root = new_sector;
        return;
    }

    Sector* current = root;
    Sector* parent = nullptr;

    while (true) {
        parent = current;

        // Decide whether to go to the left or right of the tree
        if (x < current->x || (x == current->x && y < current->y) || (x == current->x && y == current->y && z < current->z)) {
            current = current->left;

            // If the left child is null, insert the new sector there
            if (current == nullptr) {
                parent->left = new_sector;
                return;
            }
        } else {
            current = current->right;

            // If the right child is null, insert the new sector there
            if (current == nullptr) {
                parent->right = new_sector;
                return;
            }
        }
    }
}

Sector* SpaceSectorBST::findSuccessor(Sector* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    // If the sector to be deleted is a leaf node, simply delete it.
    // If the sector to be deleted has only one child, replace it with its child.
    // If the sector to be deleted has two children, replace it with its in-order successor.



}

void SpaceSectorBST::displaySectorsInOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    displaySectorsInOrderHelper(node->left);
    std::cout << node->sector_code << std::endl;
    displaySectorsInOrderHelper(node->right);
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
    cout << "Space sectors inorder traversal:" << endl;
    displaySectorsInOrderHelper(root);
    cout << endl;
}

void SpaceSectorBST::displaySectorsPreOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    std::cout << node->sector_code << std::endl;
    displaySectorsPreOrderHelper(node->left);
    displaySectorsPreOrderHelper(node->right);
}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors preorder traversal:" << endl;
    displaySectorsPreOrderHelper(root);
    cout << endl;
}

void SpaceSectorBST::displaySectorsPostOrderHelper(Sector* node) {
    if (node == nullptr) {
        return;
    }

    displaySectorsPostOrderHelper(node->left);
    displaySectorsPostOrderHelper(node->right);
    std::cout << node->sector_code << std::endl;
    
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    displaySectorsPostOrderHelper(root);
    cout << endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}
