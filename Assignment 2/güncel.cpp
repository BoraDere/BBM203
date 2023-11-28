#include "BlockFall.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

vector<vector<bool>> BlockFall::rotate(Block* block) {
    // to rotate left, we need to transpose the matrix and then reverse each column
    int rowSize = block->shape.size();
    int colSize = block->shape[0].size();

    vector<vector<bool>> newShape(colSize, vector<bool>(rowSize));

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {

            newShape[j][i] = active_rotation->shape[i][j];
        }
    }

    reverse(newShape.begin(), newShape.end());

    return newShape;
}

// function to print the grid
void BlockFall::print_grid() {
    // printing the grid according to the cell being occupied or not
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                cout << occupiedCellChar;
            } 
            else {
                cout << unoccupiedCellChar;
            }
        }
        cout << endl;
    }
}

// void BlockFall::move_right() {
//     int rowSize = active_rotation->shape.size();
//     int colSize = active_rotation->shape[0].size();

//     bool canMove = true;

//     for (int i = 0; i < rowSize; i++) {
//         if (active_rotation->colIndex + colSize <= cols) {
//             if (active_rotation->shape[i][colSize - 1] == 1 && grid[i][active_rotation->colIndex + colSize] == 1) {
//                 canMove = false;
//                 break;
//             }
//         }
//         else {
//             return;
//         }
//     }

//     if (canMove) {
//         for (int i = 0; i < rowSize; i++) {
//             for (int j = colSize - 1; j >= 0; j--) {
//                 if (active_rotation->shape[i][j] == 1) {
//                     grid[i][active_rotation->colIndex + j + 1] = 1;
//                     grid[i][active_rotation->colIndex + j] = 0;
//                 }
//             }
//         }
//         active_rotation->colIndex++;
//     }
// }

// void BlockFall::move_left() {
//     int rowSize = active_rotation->shape.size();
//     int colSize = active_rotation->shape[0].size();

//     bool canMove = true;

//     for (int i = 0; i < rowSize; i++) {
//         if (active_rotation->colIndex - 1 >= 0) {
//             if (active_rotation->shape[i][0] == 1 && grid[i][active_rotation->colIndex - 1] == 1) {
//                 canMove = false;
//                 break;
//             }
//         }
//         else {
//             return;
//         }
//     }

//     if (canMove) {
//         for (int i = 0; i < rowSize; i++) {
//             for (int j = 0; j < colSize; j++) {
//                 if (active_rotation->shape[i][j] == 1) {
//                     grid[i][active_rotation->colIndex - 1] = 1;
//                     grid[i][active_rotation->colIndex] = 0;
//                 }
//             }
//         }
//         active_rotation->colIndex--;
//     }
// }

void BlockFall::read_blocks(const string &input_file) {
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    initial_block = nullptr;
    active_rotation = nullptr;
    Block* firstBlock = nullptr;
    Block* prevBlock = nullptr;

    ifstream infile(input_file);

    if (infile.is_open()) {
        string line;
        vector<vector<bool>> block;  
        int rowSize = 0;
        int bs = 0;

        while (getline(infile, line)) {
            std::cout << "bs: " << bs << std::endl;
            if (line.empty()) {
                // Skip empty lines
                continue;
            }

            if (line.front() == '[') {
                block.clear();
                rowSize = line.length() - 1;
                line = line.substr(1);
            }

            istringstream iss(line);
            char c;

            vector<bool> row;

            for (int i = 0; i < rowSize; i++) {
                iss.get(c);
                if (c == '0' || c == '1') {
                    row.push_back(bool(c - '0'));
                }
            }
            block.push_back(row);

            if (line.back() == ']') {
                // End of the current block, add it to the list
                if (firstBlock == nullptr) {
                    // If it's the first block, set it as the initial block
                    firstBlock = new Block(block);
                    initial_block = firstBlock;
                    active_rotation = firstBlock;
                    std::cout << "ifteyim " << bs << std::endl;
                } else {
                    // Link the new block to the previous block
                    prevBlock->next_block = new Block(block);
                    std::cout << "elsteyim " << bs << std::endl;
                }
                std::cout << "ciktim " << bs << std::endl;
                // Move the prevBlock pointer to the new block
                prevBlock = new Block(block);
                std::cout << "ciktim2 " << bs << std::endl;
                rowSize = 0;
            }
            bs++;
        }
        
        infile.close();
    }

    //power_up = blocks[blocks.size() - 1];
    //blocks.pop_back();
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    //       Note that the "initial_block" member variable must be set to the first block in the linked list.
    //       Also note that the "active_rotation" member variable must be set to the first block in the linked list.
    //       The "power_up" member variable must be set to the last block in the blocks and it must not be added to the linked list.

    // for (int i = 0; i < blocks.size(); i++) {
    //     Block* newBlock = blocks[i];

    //     if (firstBlock == nullptr) {
    //         // If it's the first block, set it as the initial block
    //         firstBlock = newBlock;
    //         initial_block = firstBlock;
    //         active_rotation = firstBlock;
    //     } else {
    //         // Link the new block to the previous block
    //         prevBlock->next_block = newBlock;
    //     }

    //     // Move the prevBlock pointer to the new block
    //     prevBlock = newBlock;
    //     }

    //     // Set the last block's next_block to nullptr
    //     if (prevBlock) {
    //         prevBlock->next_block = nullptr;
    // }


    // for (int i = 0; i < blocks.size() - 1; i++) {
    //     std::cout << blocks[i] << std::endl;
    //     initial_block = blocks[i];
    //     active_rotation = initial_block;
    //     Block* b1 = new Block(rotate(initial_block));
    //     Block* b2 = new Block(rotate(b1));
    //     Block* b3 = new Block(rotate(b2));

    //     initial_block->right_rotation = b1;
    //     b1->right_rotation = b2;
    //     b2->right_rotation = b3;
    //     b3->right_rotation = initial_block;

    //     initial_block->left_rotation = b3;
    //     b1->left_rotation = initial_block;
    //     b2->left_rotation = b1;
    //     b3->left_rotation = b2;
    // }

    // Block* currentBlock = firstBlock;  // Start with the first block in the linked list

    // while (currentBlock) {

    //     // Create rotations and connect them to each other
    //     Block* b1 = new Block(rotate(currentBlock));
    //     Block* b2 = new Block(rotate(b1));
    //     Block* b3 = new Block(rotate(b2));

    //     currentBlock->right_rotation = b1;
    //     b1->right_rotation = b2;
    //     b2->right_rotation = b3;
    //     b3->right_rotation = currentBlock;

    //     currentBlock->left_rotation = b3;
    //     b1->left_rotation = currentBlock;
    //     b2->left_rotation = b1;
    //     b3->left_rotation = b2;

    //     // Move to the next block in the linked list
    //     currentBlock = currentBlock->next_block;
    // }

    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
    // Example code for reading blocks and initializing initial_block:
    // ifstream infile(input_file);
    // vector<vector<vector<bool>>> blocks;
    // // ... (read blocks from file into 'blocks' vector)
    // for (const auto &block_shape : blocks) {
    //     Block *new_block = new Block(block_shape);
    //     // TODO: Generate rotations and add to linked list
    //     // ... (add new_block to linked list)
    // }
    // initial_block = /* ... (set initial_block to the first block in the linked list) */;
}



void BlockFall::initialize_grid(const string &input_file) {
    // TODO: Initialize "rows" and "cols" member variables
    ifstream infile(input_file);

    if (infile.is_open()) {
        rows = 0;
        cols = 0;

        string line;

        while (getline(infile, line)) {
            rows++;
            if (cols == 0) {
                istringstream iss(line);
                char c;
                while (iss.get(c)) {
                    if (c == '0' || c == '1') {
                        cols++;
                    }
                }
            }
        }

        infile.clear();
        infile.seekg(0, ios::beg);

        grid.resize(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                infile >> grid[i][j];
            }
        }

        infile.close();

        // TODO: Initialize "grid" member variable using the command-line argument 1 in main
    }

}

BlockFall::~BlockFall() {
    // Free dynamically allocated memory used for storing game blocks
    Block* current = initial_block;
    Block* next;

    while (current != nullptr) {
        next = current->next_block;
        delete current;
        current = next;
    }

    initial_block = nullptr;
    active_rotation = nullptr;


}