#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:
    vector<vector<bool> > shape; // Two-dimensional vector corresponding to the block's shape
    int colIndex = 0;
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

    // Constructor
    Block(const vector<vector<bool>> &block_shape) : shape(block_shape), right_rotation(nullptr), left_rotation(nullptr), next_block(nullptr) {}
    Block() {};
};


#endif //PA2_BLOCK_H
