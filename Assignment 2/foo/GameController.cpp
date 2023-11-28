#include "GameController.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

std::string trim(const std::string& str) {
    auto start = std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isspace(c); });
    auto end = std::find_if(str.rbegin(), str.rend(), [](unsigned char c) { return !std::isspace(c); }).base();
    return (start < end) ? std::string(start, end) : std::string();
}

bool GameController::play(BlockFall &game, const string &commands_file) {
    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.
    ifstream infile(commands_file);
    
    // commands are PRINT_GRID, ROTATE_RIGHT, ROTATE_LEFT, MOVE_LEFT, MOVE_RIGHT, DROP, GRAVITY_SWITCH
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            line = trim(line);

            if (line.empty()) {
                continue;
            }

            if (line == "PRINT_GRID") {
                game.print_grid();
            }
            else if (line == "ROTATE_RIGHT") {
                //game.rotate_right();
            }
            else if (line == "ROTATE_LEFT") {
                //game.rotate_left();
            }
            else if (line == "MOVE_LEFT") {
                //game.move_left();
            }
            else if (line == "MOVE_RIGHT") {
                //game.move_right();
            }
            else if (line == "DROP") {
                //game.drop();
            }
            else if (line == "GRAVITY_SWITCH") {
                //game.gravity_switch();
            }
            else {
                std::cout << "Unknown command: " << line << endl;
            }
        }
        infile.close();
    }
    return false;
}
