#ifndef PA2_GAMECONTROLLER_H
#define PA2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

std::string trim(const std::string& str);

class GameController {
public:
    bool play(BlockFall &game, const string &commands_file); // Function that implements the gameplay
};


#endif //PA2_GAMECONTROLLER_H
