#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<vector<char>> initialiseBoard() {
    //initialise the gameboard
    vector<vector<char>> board;
    vector<char> rowVector;
    for (int i=0; i<6; i++)
    {
        rowVector.clear();
        for (int j=0; j<6; j++)
            rowVector.push_back(' ');
        board.push_back(rowVector);
    }
    board[2][2] = 'O';
    board[2][3] = 'X';
    board[3][2] = 'X';
    board[3][3] = 'O';
    return board;
}

void displayBoard(const vector<vector<char>> &board) {
    //display the gameboard onscreen
    vector<char> rowNames{'a', 'b', 'c', 'd', 'e', 'f'};
    cout << "   1 2 3 4 5 6 \n";
    cout << "---------------\n";
    for (int i=0; i<6; i++) {
        cout << rowNames[i] << " |";
        for (int j=0; j<6; j++) {
            cout << board[i][j] << "|";
        }
        cout << "\n";
        cout << "---------------\n";
    }
    cout << "\n";
}

void checkForSandwich(vector<vector<int>> &targetSquares, int inputRow, int inputColumn, char currentPlayer, const vector<vector<char>> &board) {
    // determine what an opposing piece should look like
    char opposingPlayer{};
    if (currentPlayer == 'X') {
        opposingPlayer = 'O';
    } else {
        opposingPlayer = 'X';
    }
    // look for opposing pieces adjacent to the input square
    for (int i=max(0,inputRow-1); i<=min(5,inputRow+1); i++) {
        for (int j=max(0,inputColumn-1); j<=min(5,inputColumn+1); j++) {
            if (board[i][j] == opposingPlayer) {
                // continue moving in that direction to see if there is a sandwich of any length
                int rowIncrement = i - inputRow;
                int columnIncrement = j - inputColumn;
                bool done{false};
                int k{2};
                while(!done) {
                    int currentRow{inputRow + k*rowIncrement};
                    int currentColumn{inputColumn + k*columnIncrement};
                    if (currentRow >= 0 && currentRow <= 5 && currentColumn >= 0 && currentColumn <= 5 && board[currentRow][currentColumn] == opposingPlayer) {
                        k += 1;
                    } else {
                        done = true;
                    }
                }
                // if we do find a sandwich of any length by moving in that direction, add the locations of all the squares to be flipped to the vector
                int finalRow{inputRow + k*rowIncrement};
                int finalColumn{inputColumn + k*columnIncrement};
                if (finalRow >= 0 && finalRow <= 5 && finalColumn >= 0 && finalColumn <= 5 && board[finalRow][finalColumn] == currentPlayer) {
                    for (int x=0; x<k-1; x++) {
                        vector<int> foundSquare{i+(x*rowIncrement), j+(x*columnIncrement)};
                        targetSquares.push_back(foundSquare);
                    }
                }
            }
        }
    }
}

void flipSquares(vector<vector<int>> &targetSquares, vector<vector<char>> &board) {
    for (int i=0; i<targetSquares.size(); i++) {
        if (board[targetSquares[i][0]][targetSquares[i][1]] == 'X') {
            board[targetSquares[i][0]][targetSquares[i][1]] = 'O';
        } else {
            board[targetSquares[i][0]][targetSquares[i][1]] = 'X';
        }
    }
}

void calculateAndDisplayScore(const vector<vector<char>> &board) {
    int xTotal{};
    int oTotal{};
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (board[i][j] == 'X') {
                xTotal += 1;
            } else if (board[i][j] == 'O') {
                oTotal += 1;
            }
        }
    }
    if (xTotal > oTotal) {
        cout << "Player X wins!\n";
    } else if (oTotal > xTotal) {
        cout << "Player O wins!\n";
    } else {
        cout << "It's a draw!\n";
    }
    cout << "----- SCORE -----\n";
    cout << "\n";
    cout << " Player O: " << oTotal << "\n";
    cout << " Player X: " << xTotal << "\n";
}

void newMove(char &currentPlayer, vector<vector<char>> &board) {
    // initialise variables for input row and column
    int inputRow{};
    int inputColumn{};
    // initialise vector to contain the locations of any disks which will be flipped
    vector<vector<int>> targetSquares;
    // loop asking for move until one is entered which will result in a disk being flipped
    while (targetSquares.size() == 0) {
        // get the input and convert it into array indices
        string response{};
        cout << "Player " << currentPlayer << ", enter a row and column (eg, e3): ";
        cin >> response;
        inputRow = (int)response[0]-97;
        inputColumn = (int)response[1]-49;
        // check to see if this is a legal move
        // if so, update targetSquares with the location of the disks that will be flipped
        if (board[inputRow][inputColumn] != ' ') {
            cout << "Disk must be placed on an empty spot!\n";
        } else {
            checkForSandwich(targetSquares, inputRow, inputColumn, currentPlayer, board);
            if (targetSquares.size() == 0) {
                cout << "Disk must be able to flip an opponent's disk.\n";
            }
        }
    }
    // place the current player's piece onto the board
    board[inputRow][inputColumn] = currentPlayer;
    // flip the appropriate opposing pieces
    flipSquares(targetSquares, board);
}

bool playerCanMove(char player, const vector<vector<char>> &board) {
    vector<vector<int>> possibleTargets;
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (board[i][j] == ' ') {
                checkForSandwich(possibleTargets, i, j, player, board);
                if (possibleTargets.size() > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    // initialise the gameboard, the current player, and a variable storing whether the game is over
    vector<vector<char>> board;
    board = initialiseBoard();
    char currentPlayer{'O'};
    bool gameOver{false};
    // display the initial gameboard
    cout << "---- REVERSI ----\n";
    displayBoard(board);
    // play the game
    while(!gameOver) {
        newMove(currentPlayer, board);
        displayBoard(board);
        // next player's turn
        char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        if (playerCanMove(nextPlayer, board)) {
            currentPlayer = nextPlayer;
        } else if (playerCanMove(currentPlayer, board)) {
            cout << "Player " << nextPlayer << " does not have a move to play! Player " << currentPlayer << " gets another go!\n";
        } else {
            gameOver = true;
        }
    }
    calculateAndDisplayScore(board);
}
