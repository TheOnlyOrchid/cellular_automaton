#include "main.h"

#include <iostream>
#include <vector>

// rules are:
// each cycle, anyone that is infected spreads their infection to anyone next to them.
// people only remain infected for 2 cycles - then are cured
// people who are just cured are immune to being infected that cycle



int main() {
    // each entry is how long until they are cured.
    std::vector<std::vector<int>> diseaseMatrix = {
        { 2, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    // 1 = tile "active" 0 = "inactive"
    // MUST be same size and shape as diseaseMatrix - or larger.
    std::vector<std::vector<bool>> matrixMask {
        { 1, 1, 1, 1 },
        { 1, 1, 1, 1 },
        { 1, 1, 1, 1 },
        { 1, 0, 0, 0 },
      };

    int numberOfCyclesToCompute = 10;

    for (int cycle = 0; cycle < numberOfCyclesToCompute; ++cycle) {
        auto inBounds = [&](int x, int y) {
            return x >= 0 &&
                   y >= 0 &&
                   x < static_cast<int>(diseaseMatrix.size()) &&
                   y < static_cast<int>(diseaseMatrix[x].size());
        };

        // write to a copy then write back, rather than directly editing
        // writes will go to copy, reads go through origional
        auto diseaseMatrixCopy = diseaseMatrix;

        // check each tile in diseaseMatrix exactly once for O(n) time
        for (int xPos = 0; xPos < diseaseMatrixCopy.size(); ++xPos) {
            for (int yPos = 0; yPos <= diseaseMatrixCopy[xPos].size(); ++yPos) {
                auto currentDiseaseTile = diseaseMatrix[xPos][yPos];
                const auto currentMaskTile = matrixMask[xPos][yPos];

                //  continue if tile is not "activated"
                if (currentMaskTile == false) {
                    continue;
                }

                // if tile is infected, skip processing
                if (currentDiseaseTile > 0) {
                    // decrement timer
                    diseaseMatrixCopy[xPos][yPos]--;
                    continue;
                }

                // check cardinal directions for adjacent disease
                for (const auto& dir : directions) {
                    int newX = xPos + dir[0];
                    int newY = yPos + dir[1];

                    if (inBounds(newX, newY) && diseaseMatrix[newX][newY]) {
                        // infect
                        diseaseMatrixCopy[xPos][yPos] = INFECTED_TIME;
                        break;
                    }
                }
            }
        }

        // write our copy back to the origional
        diseaseMatrix = diseaseMatrixCopy;

        // print matrix
        for (const auto& row : diseaseMatrix) {
            for (const auto& item : row) {
                std::cout << item << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n' << '\n' << '\n';
    }

    return 0;
}