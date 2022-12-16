#include <fstream>
#include <iostream>
#include <set>

using namespace std;

namespace day08 {
    const int SIZE = 99;

    int scenic_score(char (&grid)[SIZE][SIZE], int x, int y) {
        char value = grid[x][y];
        int neighboursBelow = 0;
        int neighboursAbove = 0;
        int neighboursLeft = 0;
        int neighboursRight = 0;

        // below
        for (int row = y + 1; row < SIZE; row++) {
            neighboursBelow++;
            if (grid[x][row] >= value) {
                break;
            }
        }

        // above
        for (int row = y - 1; row >= 0; row--) {
            neighboursAbove++;
            if (grid[x][row] >= value) {
                break;
            }
        }

        // right
        for (int col = x + 1; col < SIZE; col++) {
            neighboursRight++;
            if (grid[col][y] >= value) {
                break;
            }
        }

        // left
        for (int col = x - 1; col >= 0; col--) {
            neighboursLeft++;
            if (grid[col][y] >= value) {
                break;
            }
        }

        return neighboursAbove * neighboursBelow * neighboursLeft * neighboursRight;
    }

    void solve() {
        ifstream infile("inputs/day08.txt");

        char grid[SIZE][SIZE];

        int row = 0;
        for (string line; getline(infile, line);) {
            for (size_t col = 0; col < line.length(); col++) {
                grid[col][row] = line.at(col);
            }
            row++;
        }

        set<tuple<int, int>> visible;

        for (int row = 0; row < SIZE; row++) {
            int rowMaxFromLeft = 0;
            // iterate each row from left
            for (int col = 0; col < SIZE; col++) {
                char value = grid[col][row];
                if (col == 0 || rowMaxFromLeft < value) {
                    rowMaxFromLeft = value;
                    visible.insert(make_tuple(col, row));
                }
            }

            int rowMaxFromRight = 0;
            // iterate each row from right
            for (int col = SIZE - 1; col >= 0; col--) {
                char value = grid[col][row];
                if (col == SIZE - 1 || rowMaxFromRight < value) {
                    rowMaxFromRight = value;
                    visible.insert(make_tuple(col, row));
                }
            }
        }

        for (int col = 0; col < SIZE; col++) {
            int colMaxFromTop = 0;
            // iterate each column from top
            for (int row = 0; row < SIZE; row++) {
                char value = grid[col][row];
                if (row == 0 || colMaxFromTop < value) {
                    colMaxFromTop = value;
                    visible.insert(make_tuple(col, row));
                }
            }

            int colMaxFromBottom = 0;
            // iterate each column from bottom
            for (int row = SIZE - 1; row >= 0; row--) {
                char value = grid[col][row];
                if (row == SIZE - 1 || colMaxFromBottom < value) {
                    colMaxFromBottom = value;
                    visible.insert(make_tuple(col, row));
                }
            }
        }

        auto p1 = visible.size();
        assert(p1 == 1794);

        int p2 = 0;
        for (int col = 0; col < SIZE; col++) {
            for (int row = 0; row < SIZE; row++) {
                p2 = max(p2, scenic_score(grid, col, row));
            }
        }
        assert(p2 == 199272);
    }

} // namespace day08