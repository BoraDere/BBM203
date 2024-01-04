#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    
    void displaySectorsInOrderHelper(Sector* node);
    void displaySectorsPreOrderHelper(Sector* node);
    void displaySectorsPostOrderHelper(Sector* node);
    Sector* findSuccessor(Sector* node);
    Sector* deleter(Sector* root, int x, int y, int z);
    std::unordered_map<std::string, std::tuple<int, int, int>> sectorMap;
    Sector* pathGetter(Sector* root, int x, int y, int z);
    void deleteTree(Sector* node);
};

#endif // SPACESECTORBST_H
