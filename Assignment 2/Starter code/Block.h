#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:
    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * next = nullptr; // Pointer to the next block in the linked list
    Block * right_rotation = nullptr; // Pointer to the block's clockwise neighbor block (its right rotation)
    Block * left_rotation = nullptr; // Pointer to the block's counter-clockwise neighbor block (its left rotation)
    Block * next_block = nullptr; // Pointer to the next_leaderboard_entry block to appear in the game

    bool operator==(const Block& other) const {
        int rowSize = shape.size();
        int colSize = shape[0].size();

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {

                if (shape[i][j] != other.shape[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Block& other) const {
        int rowSize = shape.size();
        int colSize = shape[0].size();

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {

                if (shape[i][j] != other.shape[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }
};


#endif //PA2_BLOCK_H
