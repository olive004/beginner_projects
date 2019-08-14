//
//  2018-10-30_main.cpp
//  PRG2reversiGame
//
//  Created by Olivia Gallup on 30/10/2018.
//  Copyright © 2018 Olivia Gallup. All rights reserved.
//

#include "2018-10-30_main.hpp"

//Assignment 1: Reversi game (Due 1600 2/11/18)
/* Game conditions:
 - print ---- REVERSI ---- at beginning
 - board: 1-6 above each board space, a-f next to each row
 - row is signified by a letter a-f, column by number 1-6. The move
 would be specified for example by 'b4'
 - disks are 'O' or 'X' (capitalized)
 - disk swapping; when player's disk is next to opponents disk, and there's
 another player's disk on other side, ALL opponent's disks between the player's
 disks get flipped; works diagonally
 - disk MUST be able to flip an opponent's disk; otherwise move is illega
 "Player O does not have a move to play."
 - disk MUST be placed next to an opponent's disk
 - disk MUST be placed on empty spot
 - players alternate; if one player cannot make a valid move, play passes
 to other player. game ends when neither player can move --> when grid is
 full, or no piece can legally be placed in any remaining squares...
 - winner or tie declared
 - score printed at the end; number of x's or o's left on the board is the
 final score of each player
 */

#include <iostream>
#include <tgmath.h>
#include <stdlib.h>
#include <string>

using namespace std;
using std::string;

#define BDIMX 6         //board dimensions of rows
#define BDIMY 6         //board dimension of columns


bool checkIfFull(char board[BDIMX][BDIMY])  {
    bool isFull = true;
    
    for(i=0; i<BDIMX; i++) {        // standard row and column iterators
        for(j=0; j<BDIMY; j++) {
            if(board[i][j] == ' ') {
                isFull = false;
            }
        }
    }
    
    return isFull;
}

bool checkMovesAvailable(char board[BDIMX][BDIMY], char enemy) {
    bool thereAreMovesLeft = false;
    bool enemiesAdjacent = false;
    
    //CHECK if any of the remaining spaces still have enemy neighbors
    int dx, dy, row, col;         // help with neighboring row and column indexing
    int enemyCount = 0;
    for(row=0; row<BDIMX; row++) {
        for(col=0; col<BDIMY; col++) {
            if(board[row][col] == ' ') {        // Indexing through all the spaces on the board
                for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors to the spaces are actally bad by checking every adjacent element
                    for(dy=-1; dy<2; dy++) {
                        if(dx!=0 && dy!=0) {        // making sure the middle element is not being considered here
                            // Here it gets a bit complicated. We want to see if the element next to our neighbor is not ALSO an enemy, and if the element after THAT isn't an enemy as well. instead of writing out an amount of if statements corresponding to the number of rows or columns-2 (since the maximum amount of enemies that can be between a player's disks is the dimensions of the board -2), we can have one for loop that iterates through that amount of possible neighboring enemies. Due to dx and dy corresponding to the rows and columns, the for loop has to be split up into two, one for row and one for columns
                            if(board[row+dx][col+dy] == enemy) {
                                enemiesAdjacent = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    //CHECK if the enemies are flippable
    
    
}

//Function to convert the char input into row numbers
int convertCharToMyInt(char inputChar, int outputInt) {
    if(inputChar == 'a') outputInt = 1;                //Converting a-f char inputs to corresponding 1-6 int's; add char identities as necessary for higher board dimensions
    if(inputChar == 'b') outputInt = 2;
    if(inputChar == 'c') outputInt = 3;
    if(inputChar == 'd') outputInt = 4;
    if(inputChar == 'e') outputInt = 5;
    if(inputChar == 'f') outputInt = 6;
    
    return outputInt;
}

char convertIntToMyChar(int inputInt) {
    char outputChar;
    
    if(inputInt == 1) outputChar = 'a';                //Converting a-f char inputs to corresponding 1-6 int's; add char identities as necessary for higher board dimensions
    if(inputInt == 2) outputChar = 'b';
    if(inputInt == 3) outputChar = 'c';
    if(inputInt == 4) outputChar = 'd';
    if(inputInt == 5) outputChar = 'e';
    if(inputInt == 6) outputChar = 'f';
    
    return outputChar;
}

//Booleans that check whether the player made an invalid move that would make them go again
bool isNeighborBad(char board[BDIMX][BDIMY], int newRow, int newCol, char enemy) {
    /* Not sure if this array syntax will work, trying a non-pointer-y method
     
     int position = newCol + (newRow-1)*(BDIMY);            //Converting the row and column into a single value that the pointer can use on the board array
     if(*board[position+1] || *board[position-1] || *board[position - BDIMY] || *board[position +BDIMY] == enemy) {
     neighborIsBad = true;
     }
     */
    int dx, dy;     // help with neighboring row and column indexing
    int enemyCount = 0;
    for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors are actally bad by checking every adjacent element
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 && dy!=0) {
                // Here it gets a bit complicated. We want to see if the element next to our neighbor is not ALSO an enemy, and if the element after THAT isn't an enemy as well. instead of writing out an amount of if statements corresponding to the number of rows or columns-2 (since the maximum amount of enemies that can be between a player's disks is the dimensions of the board -2), we can have one for loop that iterates through that amount of possible neighboring enemies. Due to dx and dy corresponding to the rows and columns, the for loop has to be split up into two, one for row and one for columns
                for(int i=0; i<BDIMX; i++) {
                    for(int j=0; j<BDIMY; j++) {
                        if(board[newRow +i*dx][newCol+j*dy] == enemy) {
                            enemyCount++;
                        }
                    }
                }
            }
        }
    }
    
    return enemyCount;
}

bool isFlippable(char board[BDIMX][BDIMY], int newRow, int newCol, int enemyCount, char player) {         // input for player here is 'X' or 'O'
    int dx, dy;
    bool canFlip = false;
    
    for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors are actally bad by checking every adjacent element
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 && dy!=0) {
                for(i=0; i<enemyCount; i++) {            //So that we don't discount the cases where a player's disk is on the other side of MULTIPLe enimes, once we know that there is an enemy next to the player's disk we have to check the adjacent neighbors as well
                    if(board[newRow +dx][newCol+i*dy] == player) {
                        canflip = true;
                    }
                    if(board[newRow +i*dx][newCol+dy] == player) {
                        canflip = true;
                    }
                }
            }
        }
    }
    
}

// Checks if the space the player is trying to put their disk on is empty
bool isSpaceFree(char board[BDIMX][BDIMY], int newRow, int newCol, char enemyPlayer) {
    bool spaceFree = true;
    
    if(board[newRow][newCol] != ' ') {
        spaceFree = false;
    }
    return spaceFree;
}

return isFull;
}

char createDashes(int colNumber) {
    char dash = '-------------'

}


int refreshBoard(char board[BDIMX][BDIMY], int newRow, int newCol, char player, char enemy) {
    for(int i=0; i<BDIMY; i++) {
        cout << i << ' ';
    }
    cout << "\n";

    for(int i=0; i<BDIMX; i++) {
        cout << convertIntToMyChar(i) << " ";
        for(int j=0; j<BDIMX; j++) {
            cout << "|" << board[i][j];
        }
        cout << "|\n";
        cout << " " << createDashes(BDIMY) << endl;
    }
    
}














int main() {
    
    bool gameplayOn = true;
    bool playerOTurn = true;
    
    char board[BDIMX][BDIMY] = {{' '}};
    int initialRow = floor(BDIMX/2);
    int initialCol = floor(BDIMY/2);       //find the middle of the board regardless of dimensions
    
    //Initialize board
    cout << "---- REVERSI ----/n" << endl;
    
    board[initialRow-1][initialCol-1] = 'O';
    board[initialRow][initialCol-1] = 'X';
    board[initialRow][initialCol] = 'O';
    board[initialRow-1][initialCol] = 'X';
    
    refreshBoard(board);
    
    //Welcome message
    cout << "Welcome to Reversi! First it is Player O's turn" << endl;
    
    
    
    
    
    while(gameplayOn) {
        //Check that the game is not over before asking for new move: is there any space left, are there any more valid moves possible for either player
        bool isfull = checkIfFull(board);
        bool playerTurn = true;             // Using 'true' to denote player O and 'false' to denote player X; makes turns easier to flip
        
        if(isfull) {
            gameplayOn = false;
            break;
        }
        bool movesPossible = checkMovesAvailable(board);
        
        if(isfull || !movesPossible) {
            gameplayOn = false;
        }

        
        
        //Player protocol

            //User input prompt
        string newMove;
        int newRow;
        int newCol;
        
        //Whos turn is it
        if(playerTurn == true) {
            char enemyDisk = 'X';
            char playerDisk = 'O';
        }
        if(playerTurn == false) {
            char enemyDisk = 'O';
            char playerDisk = 'X';
        }
        
            

        // keep repeating user input prompt as long as it is the player's turn
        do {

                //Getting the next move
                newMove = prompt();
                //Converting the user's input of a char followed by an int into two ints specifying the row and column that the next move will be in
                newRow = convertCharToMyInt(newMove.at(0)) -1;            // Minus 1 to make array indexing easier
                newCol = newMove.at(1) -1;
                
                
                //Errors after move
                //Checking that move is valid; if error, the player gets to go again:
                
                //check how many adjacent enemy neighbors and amount of enemy neighbors there are
                bool neighborAnEnemy = isNeighborBad(board, newRow, newCol, enemyDisk);
                
                // if there is an enemy neighbor, check if there's a friend on other side
                if(neighborAnEnemy) {
                    bool canFlip = isFlippable(board, newRow, newCol,  playerDisk);
                }
                bool spaceFree = isSpaceFree(board, newRow, newCol);      //this is not a test of whether the whole board is taken, just space @ the new move
                
                
                //Error messages: Player O can try again
                if(!spaceFree) {
                    cout << "This spot is taken already, try another one" << endl;
                }
                if(!neighborAnEnemy) {
                    cout << "Disk must be placed next to an opponent's disk." << endl;
                }
                if(!canFlip) {
                    cout << "Disk must be able to flip an opponent's disk." << endl;
                }

        }while(!neighborAnEnemy || !canFlip || !spaceFree);
        
        refreshBoard(board, newRow, newCol, playerDisk, enemyDisk);
        
        // Other player's turn
        playerTurn = !playerTurn;
                
                
    }
        
        
        

    
    //Adding input to array, dissecting row and column
    //Convert inbetween opponents (inbetweeners)
    
    //Turn goes to Player O
    
}








