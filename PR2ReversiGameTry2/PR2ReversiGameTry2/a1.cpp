//
//  2018-10-30_main.cpp
//  PRG2reversiGame
//
//  Created by Olivia Gallup on 30/10/2018.
//  Copyright © 2018 Olivia Gallup. All rights reserved.
//

// NOTES ON THE GAME
//Assignment 1: Reversi game (Due 1600 2/11/18)
//Game conditions:
// -- print ---- REVERSI ---- at beginning
// -- board: 1-6 above each board space, a-f next to each row
// - row is signified by a letter a-f, column by number 1-6. The move
// would be specified for example by 'b4'
// -- disks are 'O' or 'X' (capitalized)
// - disk swapping; when player's disk is next to opponents disk, and there's
// another player's disk on other side, ALL opponent's disks between the player's
// disks get flipped; works diagonally
// - disk MUST be able to flip an opponent's disk; otherwise move is illega
// "Player O does not have a move to play."
// - disk MUST be placed next to an opponent's disk
// - disk MUST be placed on empty spot
// - players alternate; if one player cannot make a valid move, play passes
// to other player. game ends when neither player can move --> when grid is
// full, or no piece can legally be placed in any remaining squares...
// - winner or tie declared
// - score printed at the end; number of x's or o's left on the board is the
// final score of each player
//




#include <iostream>
#include <tgmath.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
using std::string;

#define BDIMX 6         //board dimensions of rows
#define BDIMY 6         //board dimension of columns



// FUNCTION HEADER
bool checkIfFull(char board[BDIMX][BDIMY])  {
    bool isFull = true;
    
    for(int i=0; i<BDIMX; i++) {        // standard row and column iterators
        for(int j=0; j<BDIMY; j++) {
            if(board[i][j] == ' ') {
                isFull = false;
            }
        }
    }
    
    return isFull;
}

bool checkMovesAvailable(char board[BDIMX][BDIMY], char enemyDisk) {
    bool thereAreMovesLeft = false;
    bool enemiesAdjacent = false;
    bool canFlip = false;
    
    //CHECK if any of the remaining spaces still have enemy neighbors
    int dx, dy, row, col;         // help with neighboring row and column indexing
    for(row=0; row<BDIMX; row++) {
        for(col=0; col<BDIMY; col++) {
            if(board[row][col] == ' ') {        // Indexing through all the spaces on the board
                for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors to the spaces are actally bad by checking every adjacent element
                    for(dy=-1; dy<2; dy++) {
                        if(dx!=0 && dy!=0) {        // making sure the middle element is not being considered here
                            // Here it gets a bit complicated. We want to see if the element next to our neighbor is not ALSO an enemy, and if the element after THAT isn't an enemy as well. instead of writing out an amount of if statements corresponding to the number of rows or columns-2 (since the maximum amount of enemies that can be between a player's disks is the dimensions of the board -2), we can have one for loop that iterates through that amount of possible neighboring enemies. Due to dx and dy corresponding to the rows and columns, the for loop has to be split up into two, one for row and one for columns
                            if(board[row+dx][col+dy] == enemyDisk) {
                                enemiesAdjacent = true;
                            }
                }
                    }
                }
            }
        }
    }
    
    
    //CHECK if the enemies are flippable
    for(int i=0; i<BDIMX; i++) {        // row iterator
        for(int j=0; j<BDIMY; j++) {        // column iterator
            for(dx= -1; dx<2; dx++) {       // row scanning, 1 unit big
                for(dy=-1; dy<2; dy++) {        // column scanning, 1 unit big
                    for(int multiplier=0; multiplier<BDIMX; multiplier++) {     // multiplier for array scanners
                        if(board[i +dx][j+ multiplier * dy] == enemyDisk) {     // if one or more enemies is detected with a subsequent space, we know the enemyDisks are flippable
                            if(board[i][j+ (multiplier+1) * dy] == ' ') {
                                canFlip = true;
                            }
                        }
                        if(board[i + multiplier * dx][j] == enemyDisk) {
                            if(board[i + (multiplier+1) * dx][j+dy] == ' ') {
                                canFlip = true;
                            }
                        }
                        if(board[i + multiplier * dx][j+ multiplier * dy] == enemyDisk) {
                            if(board[i + (multiplier+1) * dx][j+dy] == ' ') {
                                canFlip = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    if(enemiesAdjacent && canFlip) {
        thereAreMovesLeft = true;
    }
    //TODO: //movesLeft cout test
    //    cout << "are there moves left" << thereAreMovesLeft << endl;
    return thereAreMovesLeft;
}


//Function to convert the char input into row numbers
int convertCharToMyInt(char inputChar) {
    int outputInt = 0;
    
    if(inputChar == 'a') outputInt = 1;                //Converting a-f char inputs to corresponding 1-6 int's; add char identities as necessary for higher board dimensions
    if(inputChar == 'b') outputInt = 2;
    if(inputChar == 'c') outputInt = 3;
    if(inputChar == 'd') outputInt = 4;
    if(inputChar == 'e') outputInt = 5;
    if(inputChar == 'f') outputInt = 6;
    
    return outputInt;
}

// Converts
char convertIntToMyChar(int inputInt) {
    char outputChar = 'a';
    
    if(inputInt == 1) outputChar = 'a';                //Converting a-f char inputs to corresponding 1-6 int's; add char identities as necessary for higher board dimensions
    if(inputInt == 2) outputChar = 'b';
    if(inputInt == 3) outputChar = 'c';
    if(inputInt == 4) outputChar = 'd';
    if(inputInt == 5) outputChar = 'e';
    if(inputInt == 6) outputChar = 'f';
    
    return outputChar;
}

//Booleans that check whether the player made an invalid move that would make them go again
bool diskOnBoard(int newRow, int newCol) {
    bool onBoard = false;
    if(newRow < BDIMX && newCol < BDIMY) {
        onBoard = true;
    }
    return onBoard;
}

bool isNeighborBad(char board[BDIMX][BDIMY], int newRow, int newCol, char enemyDisk) {
    /* Not sure if this array syntax will work, trying a non-pointer-y method
     
     int position = newCol + (newRow-1)*(BDIMY);            //Converting the row and column into a single value that the pointer can use on the board array
     if(*board[position+1] || *board[position-1] || *board[position - BDIMY] || *board[position +BDIMY] == enemy) {
     neighborIsBad = true;
     }
     */
    int dx, dy;     // help with neighboring row and column indexing
    bool neighborBad = false;
    
    for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors are actally bad by checking every adjacent element
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 && dy!=0) {
                // Here it gets a bit complicated. We want to see if the element next to our neighbor is not ALSO an enemy, and if the element after THAT isn't an enemy as well. instead of writing out an amount of if statements corresponding to the number of rows or columns-2 (since the maximum amount of enemies that can be between a player's disks is the dimensions of the board -2), we can have one for loop that iterates through that amount of possible neighboring enemies. Due to dx and dy corresponding to the rows and columns, the for loop has to be split up into two, one for row and one for columns
                for(int i=0; i<BDIMX; i++) {
                    for(int j=0; j<BDIMY; j++) {
                        if(board[newRow +i * dx][newCol+j * dy] == enemyDisk) {
                            neighborBad = true;
                        }
                    }
                }
            }
        }
    }
    //TODO: //cout test
    //    cout << "neighbor is an enemy? " << neighborBad << endl;
    
    return neighborBad;
}


bool isFlippable(char board[BDIMX][BDIMY], int newRow, int newCol, char playerDisk, char enemyDisk) {         // player disk and enemy disk are just 'X' or 'O'
    int dx, dy, rowCheck, columnCheck;          // rowCheck and columnCheck are just temporary variables to hold the iterations of each adjacent row and column that is checked for enemies
    bool canFlip = false;
    
    //    cout<< "newRow: " << newRow << endl;
    //    cout<< "newCol: " << newCol << endl;
    //
    for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors are actally bad by checking every adjacent element
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 && dy!=0) {
                //                cout << "dx: " << dx << "  dy: " << dy << endl;
                for(int multiplier=1; multiplier<=BDIMX; multiplier++) {            //So that we don't discount the cases where a player's disk is on the other side of MULTIPLe enimes, once we know that there is an enemy next to the player's disk we have to check the adjacent neighbors as well
                    //                    cout << "multiplier: " << multiplier << endl;
                    //                    cout << "board[newRow][newCol+multiplier * dy]: " << board[newRow][newCol+multiplier * dy] << endl;
                    rowCheck = newRow + multiplier * dx;
                    columnCheck = newCol+multiplier * dy;
                    //                    cout<< "rowCheck" << rowCheck << endl;
                    //                    cout << "columnCheck" << columnCheck << endl;
                    //
                    if(rowCheck >=0 && rowCheck<BDIMX && columnCheck >=0 && columnCheck<BDIMY) {
                        if(board[newRow][columnCheck] == enemyDisk) {
                            if(board[newRow][newCol + (multiplier+1) * dy] == playerDisk) {
                                canFlip = true;
                                //                            cout << "!!!columnCheck: " << columnCheck << endl;
                                //                            cout << "!!!newCol + (multiplier+1) * dy: " << (newCol + (multiplier+1) * dy) << endl;
                                //                            cout << "canFlip: " << canFlip << endl;
                            }
                        }
                        //                    cout<< "board[rowCheck][newCol]: " << board[rowCheck][newCol] << endl;
                        if(board[rowCheck][newCol] == enemyDisk) {
                            if(board[newRow + (multiplier+1) * dx][newCol] == playerDisk) {
                                canFlip = true;
                                //                            cout << "!!!rowCheck: " << rowCheck << endl;
                                //                            cout << "!!!newRow + (multiplier+1) * dx: " << (newRow + (multiplier+1) * dx) << endl;
                                //                            cout << "canFlip: " << canFlip << endl;
                            }
                        }
                        //                    cout<< "board[rowCheck][columnCheck]: " << board[rowCheck][columnCheck] << endl;
                        if(board[rowCheck][columnCheck] == enemyDisk) {
                            if(board[newRow + (multiplier+1) * dx][newCol + (multiplier+1) * dy] == playerDisk) {
                                canFlip = true;
                                //                            cout << "!!!columnCheck: " << columnCheck << endl;
                                //                            cout << "!!!newCol + (multiplier+1) * dy: " << (newCol + (multiplier+1) * dy) << endl;
                                //                            cout << "!!!rowCheck: " << rowCheck << endl;
                                //                            cout << "!!!newRow + (multiplier+1) * dx: " << (newRow + (multiplier+1) * dx) << endl;
                                //                            cout << "canFlip: " << canFlip << endl;
                                
                            }
                        }
                    }
                }
            }
        }
    }
    //TODO: //cout test
    //    cout<< "can the enemies be flipped? " << canFlip << endl;
    
    return canFlip;
}

// Checks if the space the player is trying to put their disk on is empty
bool isSpaceFree(char board[BDIMX][BDIMY], int newRow, int newCol, char enemyPlayer) {
    bool spaceFree = true;
    
    if(board[newRow][newCol] == 'X' || board[newRow][newCol] == 'O') {
        spaceFree = false;
    }
    return spaceFree;
}

void createDashes(int colNumber) {
    cout << " ";
    for(int i=0; i< (2 * colNumber +1); i++) {
        cout<< "-";
    }
}

string prompt(char playerDisk) {
    string newMove;
    cout << "Player " << playerDisk << ", enter a row and column (eg, e3): ";
    cin >> newMove;
    cout << "\n\n\n";
    
    return newMove;
}


void resetBoard(char board[BDIMX][BDIMY]) {
    // Creating numbers
    cout << "   ";
    for(int i=1; i<=BDIMY; i++) {
        cout << i << " ";
    }
    cout << "\n";
    
    // Creating letters and board
    for(int i=0; i<BDIMX; i++) {
        // letters
        cout << convertIntToMyChar(i+1) << " ";
        
        // board
        for(int j=0; j<BDIMX; j++) {
            cout << "|" << board[i][j];
        }
        cout << "|\n";  //closing |
        
        // dashes between the rows
        cout << " ";
        createDashes(BDIMY);
        cout << "\n";
    }
    cout << "\n";
}

void refreshBoard(char board[BDIMX][BDIMY], int newRow, int newCol, char playerDisk, char enemyDisk) {
    board[newRow][newCol] = playerDisk;
    
    // Try 2 for flipping enemies
    //    vector<int> rowEnemyCounter(BDIMX-1);
    //    vector<int> colEnemyCounter(BDIMY-1);
    //    int dx, dy, rowCheck, columnCheck, rowCheckPlus, rowCheckMinus, columnCheckPlus, columnCheckMinus ;         // dy dx are row, column scanning indexes       // rowCheck and columnCheck are just temporary variables to hold the iterations of each adjacent row and column that is checked for enemies;
    
    //    for(dx=-1; dx<2; dx++) {
    //        for(dy=-1; dy<2; dy++) {
    //            if(dx!=0 || dy!=0) {
    //                rowCheck = newRow;
    //                columnCheck = newCol;
    //                rowCheck += dx;
    //                columnCheck += dy;
    //
    //                cout << "1rowCheck " << rowCheck << "      columnCheck" << columnCheck << endl;
    //
    //                if(diskOnBoard(rowCheck, columnCheck) && board[rowCheck][columnCheck] == enemyDisk) {
    //                    while(board[rowCheck][columnCheck] == enemyDisk) {
    //                        if(!diskOnBoard((rowCheck +dx), (columnCheck + dy))) {
    //                            break;
    //                        }
    //                        rowCheck += dx;
    //                        columnCheck += dy;
    //                        cout << "2rowCheck " << rowCheck << "      columnCheck" << columnCheck << endl;
    //
    //                    }
    //                    if(!diskOnBoard(rowCheck, columnCheck)) {
    //                        continue;
    //                    }
    //                    if(board[rowCheck][columnCheck] == playerDisk) {
    //                        do {
    //                            rowCheck -= dx;
    //                            columnCheck -= dy;
    //                            rowEnemyCounter.push_back(rowCheck);
    //                            colEnemyCounter.push_back(columnCheck);
    //                            cout << "3rowCheck " <<rowCheck << "     columnCheck" << columnCheck << endl;
    //                        } while(rowCheck != newRow && columnCheck != newCol);
    //                    }
    //                }
    //           }
    //       }
    //   }
    //    cout << "size of enemy vector " << rowEnemyCounter.size() << " by " << colEnemyCounter.size() << endl;
    //    for(int i=0; i<rowEnemyCounter.size(); i++) {
    //        for(int j=0; j<colEnemyCounter.size(); j++) {
    //            cout << "new enemy " << board[rowEnemyCounter[i]][colEnemyCounter[j]] << endl;
    //            board[rowEnemyCounter[i]][colEnemyCounter[j]] = enemyDisk;
    //        }
    //    }
    
    
    
    
    //Try 1 for flipping enemies
    int dx, dy, rowCheck, columnCheck, rowCheckPlus, rowCheckMinus, columnCheckPlus, columnCheckMinus ;         // dy dx are row, column scanning indexes       // rowCheck and columnCheck are just temporary variables to hold the iterations of each adjacent row and column that is checked for enemies;
    
    for(dx=-1; dx<2; dx++) {
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 || dy!=0) {
                for(int multiplier=1; multiplier<=BDIMX; multiplier++) {            //So that we don't discount the cases where a player's disk is on the other side of MULTIPLe enimes, once we know that there is an enemy next to the player's disk we have to check the adjacent neighbors as well using a multiplier
                    
                    rowCheck = newRow + multiplier * dx;
                    rowCheckPlus = newRow + (multiplier+1) * dx;
                    rowCheckMinus = newRow + (multiplier-1) * dx;
                    columnCheck = newCol+multiplier * dy;
                    columnCheckPlus = newCol+ (multiplier+1) * dy;
                    columnCheckMinus = newCol+ (multiplier-1) * dy;
                    
                    if(rowCheck >=0 && rowCheck<BDIMX   && columnCheck >= 0 && columnCheck <BDIMY) {
                        //Check that there's no space between the player's disk and the disk it should flip; otherwise if there's a friend next to an enemy but the disk put down is one or more spaces away, the enemy will be flipped anyway
                        
                        
                        //                    cout << "dx " << dx << "   dy " << dy << endl;
                        //                    cout<< "rowCheck: " << rowCheck << "     columnCheck: " << columnCheck << endl;
                        
                        //                        cout<< "board[newRow][columnCheck] " << board[newRow][columnCheck] << endl;
                        
                        // Checking horizontally
                        if(board[newRow][columnCheck] == enemyDisk) {
                            if(board[newRow][columnCheckPlus] == playerDisk) {
                                //                                cout << "multiplier check: " << columnCheck << (columnCheckPlus) << (columnCheckPlus) << "between disks " << board[newRow][columnCheckPlus] << "."<< endl;
                                //                                cout << "!!! board[newRow][newCol + (multiplier+1) * dy] " << board[newRow][columnCheckPlus] << endl;
                                if(board[newRow][columnCheckPlus] != ' ') {
                                    board[newRow][columnCheck] = playerDisk;
                                }
                            }
                        }
                        //                        cout << "board[rowCheck][newCol]" << board[rowCheck][newCol] << endl;
                        
                        // Checking vertically
                        if(board[rowCheck][newCol] == enemyDisk) {
                            if(board[rowCheckPlus][newCol] == playerDisk) {
                                //                                cout << "multiplier check: " << rowCheck<<  (rowCheckPlus) << (rowCheckMinus) << "between disks " << board[rowCheckMinus][newCol] << "." << endl;
                                //                                cout << "!!!board[newRow + (multiplier+1) * dx][newCol]: " << board[rowCheckPlus][newCol] << endl;
                                if(board[rowCheckMinus][newCol] != ' ') {
                                    board[rowCheck][newCol] = playerDisk;
                                }
                            }
                        }
                        //                        cout << "board[rowCheck][columnCheck]" << board[rowCheck][columnCheck]<< endl;
                        
                        // Checking diagonally
                        if(board[rowCheck][columnCheck] == enemyDisk) {
                            if(board[rowCheckPlus][columnCheckPlus] == playerDisk) {
                                //                                cout << "multiplier check: " << rowCheck << (rowCheckPlus) << (rowCheckMinus) << "  between disks " << board[rowCheckMinus][columnCheckPlus] << "."<< endl;
                                //                                cout << "!!!board[newRow + (multiplier+1) * dx][newCol + (multiplier+1) * dy] " << board[rowCheckPlus][newCol + (multiplier+1) * dy] << endl;
                                //if((board[rowCheckMinus][columnCheckPlus]) != ' ') {}
                                
                                board[rowCheck][columnCheck] = playerDisk;
                                
                            }
                        }
                    }
                }
            }
        }
    }
    
    // DRAWING BOARD
    // Creating numbers
    
    cout << "   ";
    for(int i=1; i<=BDIMY; i++) {
        cout << i << " ";
    }
    cout << "\n";
    
    // Creating letters and board
    for(int i=0; i<BDIMX; i++) {
        // letters
        cout << convertIntToMyChar(i+1) << " ";
        
        // board
        for(int j=0; j<BDIMX; j++) {
            cout << "|" << board[i][j];
        }
        cout << "|\n";  //closing |
        
        // dashes between the rows
        cout << " ";
        createDashes(BDIMY);
        cout << "\n";
    }
    cout << "\n";
}

void showScore(char board[BDIMX][BDIMY]) {
    int xScore = 0;
    int oScore = 0;
    
    for(int i=0; i<BDIMX; i++) {        //row iteration
        for(int j=0; j<BDIMY; j++) {        //column iteration
            if(board[i][j] == 'X') {
                ++xScore;
            }
            if(board[i][j] == 'O') {
                ++oScore;
            }
        }
    }
    if(xScore < oScore) {
        cout << "Player X wins!! omg\n" << endl;
    } else {
        cout << "Player O wins!! omg\n" << endl;
    }
    
    cout << "----- SCORE -----" << endl;
    cout << "Player O: " << oScore << endl;
    cout << "Player X: " << xScore << endl;
}





int main() {
    
    bool gameplayOn = true;
    
    char board[BDIMX][BDIMY];
    
    int initialRow = floor(BDIMX/2);
    int initialCol = floor(BDIMY/2);       //find the middle of the board regardless of dimensions
    
    //Initialize board
    cout << "---- REVERSI ----\n" << endl;
    for(int i=0; i<BDIMX; i++) {
        for(int j=0; j<BDIMY; j++) {
            board[i][j] = ' ';
        }
    }
    
    board[initialRow-1][initialCol-1] = 'O';
    board[initialRow][initialCol-1] = 'X';
    board[initialRow][initialCol] = 'O';
    board[initialRow-1][initialCol] = 'X';
    
    resetBoard(board);
    
    //Welcome message
    cout << "Welcome to Reversi! Type 'quit' to quit. First it is Player O's turn." << endl;
    
    
    
    bool playerTurn = true;             // Using 'true' to denote player O and 'false' to denote player X; makes turns easier to flip
    
    while(gameplayOn) {
        //Check that the game is not over before asking for new move: is there any space left, are there any more valid moves possible for either player
        bool isFull = checkIfFull(board);
        
        
        //Player protocol
        
        //User input var's
        string newMove;
        int newRow = 0;
        int newCol = 0;
        char enemyDisk='a';
        char playerDisk='a';
        
        //Whos turn is it
        if(playerTurn == 1) {
            enemyDisk = 'X';
            playerDisk = 'O';
        }
        if(playerTurn == 0) {
            enemyDisk = 'O';
            playerDisk = 'X';
        }
        
        bool movesPossible = checkMovesAvailable(board, enemyDisk);
        if(isFull || !movesPossible) {
            gameplayOn = false;
            break;
        }
        
        
        // booleans for checking if the player can go again
        bool canFlip = false;
        bool neighborAnEnemy = false;
        bool spaceFree = false;
        bool onBoard = false;
        // keep repeating user input prompt as long as it is the player's turn
        do {
            //Getting the next move
            newMove = prompt(playerDisk);
            
            if(newMove == "quit") {
                gameplayOn = false;
                break;
            }
            
            //Converting the user's input of a char followed by an int into two ints specifying the row and column that the next move will be in
            newRow = convertCharToMyInt(newMove.at(0)) -1;            // Minus 1 to make array indexing easier
            newCol = newMove.at(1) -49;             // Minus 1 for indexing, and minus 48 to convert from ascii int to a normal int
            
            
            //Errors after move
            //Checking that move is valid; if error, the player gets to go again:
            
            // is newMove on board
            onBoard = diskOnBoard(newRow, newCol);
            // check if adjacent is an enemy
            neighborAnEnemy = isNeighborBad(board, newRow, newCol, enemyDisk);
            canFlip = isFlippable(board, newRow, newCol, playerDisk, enemyDisk);
            spaceFree = isSpaceFree(board, newRow, newCol, enemyDisk);      //this is not a test of whether the whole board is taken, just space @ the new move
            
            
            //Error messages: Player O can try again
            if(!onBoard) {
                cout << "This is not on the board, please try again." << endl;
            } else if(!spaceFree) {
                cout << "This spot is taken already, try another one." << endl;
            } else if(!neighborAnEnemy) {
                cout << "Disk must be placed next to an opponent's disk." << endl;
            } else if(!canFlip) {
                cout << "Disk must be able to flip an opponent's disk." << endl;
            }
            
        }while(!onBoard || !neighborAnEnemy || !canFlip || !spaceFree);
        
        if(onBoard && neighborAnEnemy && canFlip && spaceFree) {
            cout << "\n" << endl;
            // This board refresh is still for current player; switch is yet to occur
            refreshBoard(board, newRow, newCol, playerDisk, enemyDisk);
            // Other player's turn
            playerTurn = !playerTurn;
            
        }
        
        
    }
    
    
    // Scoreboard
    showScore(board);
    
    return 0;
    
}
