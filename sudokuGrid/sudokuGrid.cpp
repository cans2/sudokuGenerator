#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class SudokuGame {
public:
    int gameGrid[9][9];
    bool gameOver;

    SudokuGame() {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                this->gameGrid[i][j] = 0;

        this->gameOver = false;
    }
};

bool isValid(SudokuGame* game, int num, int row, int col) {
    // Check if num is already present in the current row or column
    for (int i = 0; i < 9; i++) {
        if (game->gameGrid[row][i] == num || game->gameGrid[i][col] == num)
            return false;
    }

    // Check if num is already present in the current 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->gameGrid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

bool fillGrid(SudokuGame* game, int row, int col) {
    if (row == 9) {
        return true;
    }

    int nextRow = col == 8 ? row + 1 : row;
    int nextCol = col == 8 ? 0 : col + 1;

    if (game->gameGrid[row][col] != 0) {
        return fillGrid(game, nextRow, nextCol);
    }

    // Shuffle the numbers 1 to 9
    int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_shuffle(nums, nums + 9);

    for (int i = 0; i < 9; i++) {
        int num = nums[i];
        if (isValid(game, num, row, col)) {
            game->gameGrid[row][col] = num;
            if (fillGrid(game, nextRow, nextCol)) {
                return true;
            }
            game->gameGrid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    srand(time(NULL));
    SudokuGame game;
    fillGrid(&game, 0, 0);

    // Printing the Sudoku grid
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6)
            cout << "-------------------" << '\n';
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6)
                cout << "| ";
            cout << game.gameGrid[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}
