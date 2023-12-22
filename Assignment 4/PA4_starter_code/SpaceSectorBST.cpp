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

    Sector* new_sector = new Sector(x, y, z);

    sectorMap[new_sector->sector_code] = std::make_tuple(x, y, z);

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

Sector* SpaceSectorBST::deleter(Sector* root, int x, int y, int z) {
    if (root == nullptr) {
        return root;
    }

    if (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z < root->z)) {
        root->left = deleter(root->left, x, y, z);
    }
    else if ((x > root->x) || (x == root->x && y > root->y) || (x == root->x && y == root->y && z > root->z)) {
        root->right = deleter(root->right, x, y, z);
    }
    else {
        if (root->left == nullptr) {
            Sector* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Sector* temp = root->left;
            delete root;
            return temp;
        }

        // two children
        Sector* temp = findSuccessor(root->right);
        cout << root->sector_code << endl;
        cout << temp->sector_code << endl;

        root->x = temp->x; root->y = temp->y; root->z = temp->z;
        root->sector_code = temp->sector_code;

        root->right = deleter(root->right, temp->x, temp->y, temp->z);
    }
    return root;
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    // If the sector to be deleted is a leaf node, simply delete it.
    // If the sector to be deleted has only one child, replace it with its child.
    // If the sector to be deleted has two children, replace it with its in-order successor.

    auto sector = sectorMap.find(sector_code);

    int x, y, z;
    std::tie(x, y, z) = sector->second;

    root = deleter(root, x, y, z);

    sectorMap.erase(sector);
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

Sector* SpaceSectorBST::pathGetter(Sector* root, int x, int y, int z) {
    if (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z < root->z)) {
        return root->left;
    }
    else {
        return root->right;
    }
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
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

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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
