//
//  main.cpp
//  PRG2reversiGame
//
//  Created by Olivia Gallup on 28/10/2018.
//  Copyright © 2018 Olivia Gallup. All rights reserved.
//

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
    bool isFull = false;
    
    for(i=0; i<BDIMX; i++) {        // standard row and column iterators
        for(j=0; j<BDIMY; j++) {
            if(board[i][j] == ' ') {
                isFull = true;
            }
        }
    }
    
    return isFull;
}





int refreshBoard(int board[BDIMX][BDIMY], int bdimx, int bdimy) {
    for(int i=0; i<bdimx; i++) {
        cout << i << ' ';
    }
    endl;
    cout << 
    
    
}

//Function to convert the char input into row numbers
int convertCharToInt(char inputChar, int newRow) {
    if(newRow == 'a') newRow = 1;                //Converting a-f char inputs to corresponding 1-6 int's; add char identities as necessary for higher board dimensions
    if(newRow == 'b') newRow = 2;
    if(newRow == 'c') newRow = 3;
    if(newRow == 'd') newRow = 4;
    if(newRow == 'e') newRow = 5;
    if(newRow == 'f') newRow = 6;
    
    return newRow;
}

//Booleans that check whether the player made an invalid move that would make them go again
int isNeighborBad(char board[BDIMX][BDIMY], int newRow, int newCol, char enemy) {
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
       
bool isFlippable(char board[BDIMX][BDIMY], int newRow, int newCol, char player) {         // input for player here is 'X' or 'O'
    int dx, dy;
    for(dx= -1; dx<2; dx++) {           // Checking whether or not the neighbors are actally bad by checking every adjacent element
        for(dy=-1; dy<2; dy++) {
            if(dx!=0 && dy!=0) {
                if(board[newRow +2*dx][newCol+2*dy] == player) {
                    
            }
        }
    }
    
}
bool isSpaceFree(board, BDIMX, BDIMY, newORow, newOCol);
       
       
       
       

       
       
       
       
       
       
       
       
       
       int main() {
           
           cout << "---- REVERSI ----/n" << endl;
           
           bool gameplayOn = true;
           bool playerOTurn = true;
           
           char board[BDIMX][BDIMY] = {{' '}};
           int initialRow = floor(BDIMX/2);
           int initialCol = floor(BDIMY/2);       //find the middle of the board regardless of dimensions
           
           //Initial board
           board[initialRow-1][initialCol-1] = 'O';
           board[initialRow][initialCol-1] = 'X';
           board[initialRow][initialCol] = 'O';
           board[initialRow-1][initialCol] = 'X';
           
           
           while(gameplayOn) {
               //Check before asking for new move: is there any space left, are there any more valid moves possible
               bool isfull = checkIfFull(board);
               if(isfull) {
                   gameplayOn = false;
                   break;
               }
               
               //Player O protocol
               if(playerOTurn) {
                   //User input prompt
                   bool isRow =true;
                   string newMove;
                   int newORow;
                   int newOCol;
                   
                   
                   do {
                       //Checking if there are any valid moves left
                       bool movesLeft = checkMovesAvailable(board, BDIMX, BDIMY);
                       if(!movesLeft) {
                           playerOTurn = false;
                           break;
                       }
                       
                       
                       //Getting the next move
                       newMove = promptO();
                       //Converting the user's input of a char followed by an int into two ints specifying the row and column that the next move will be in
                       newORow = convertCharToInt(newMove.at(0)) -1;
                       newOCol = newMove.at(1) -1;
                       
                       
                       //Checking that move is valid; if error, the player gets to go again
                       int hasNeighbor = isNeighborBad(board, newORow, newOCol, 'O');
                       // if there is an enemy neighbor, check if there's a friend on other side
                       if(hasNeighbor > 0) {
                           bool canFlip = isFlippable(board, newORow, newOCol, 'O');
                       }
                       bool spaceFree = isSpaceFree(board, newORow, newOCol, 'O');      //this is not a test of whether the whole board is taken, just space @ new move
                       
                       
                       //Error messages: Player O can try again
                       if(!spaceFree) {
                           cout << "This spot is taken already, try another one" << endl;
                       }
                       if(hasNeighbor ==0) {
                           cout << "Disk must be placed next to an opponent's disk." << endl;
                       }
                       if(!canFlip) {
                           cout << "Disk must be able to flip an opponent's disk." << endl;
                       }
                       
                   } while(hasNeighbor==0 || !canFlip || !spaceFree)
                       
                       
                       }
               
               
               
               
               
               
               
               //Player X Protocol
               if(playerXTurn) {
                   
                   
                   
                   
                   
               }
               
           }
           
           
           
           
           //Adding input to array, dissecting row and column
           
           //Convert inbetween opponents (inbetweeners)
           
           
           //Turn goes to Player O
           
       }
       
       
       
       
       
       
