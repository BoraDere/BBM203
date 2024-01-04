#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    void displaySectorsInOrderHelper(Sector* node);
    void displaySectorsPreOrderHelper(Sector* node);
    void displaySectorsPostOrderHelper(Sector* node);
    Sector* pathGetter(Sector* root, int x, int y, int z);
    std::unordered_map<std::string, std::tuple<int, int, int>> sectorMap;
    Sector* insert(Sector* node, int x, int y, int z);
    bool isRed(Sector* node);
    Sector* rotateLeft(Sector* node);
    Sector* rotateRight(Sector* node);
    void flip(Sector* node);
    void deleteTree(Sector* node);
};

#endif // SPACESECTORLLRBT_H
