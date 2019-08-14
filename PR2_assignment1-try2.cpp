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

#define BDIMX 6         //board dim of rows
#define BDIMY 6         //board dimension of columns

int refreshBoard(int board[BDIMX][BDIMY], int bdimx, bdimy);

int main() {
    cout << "---- REVERSI ----/n" << endl;

    bool gameplayOn = true;
    bool playerOTurn = true;

    char board[BDIMX][BDIMY] = {{' '}};
    int initializeRow = floor(BDIMX/2);       
    int initializeCol = floor(BDIMY/2);       //find the middle of the board

    //Initial board
    board[initializeRow-1][initializeCol-1] = 'O';
    board[initializeRow][initializeCol-1] = 'X';
    board[initializeRow][initializeCol] = 'O';
    board[initializeRow-1][initializeCol] = 'X';

    while(gameplayOn) {
        //Check before asking for new move: is there any space left, are there any more valid moves possible
        bool isfull = checkIfFull(board, BDIMX, BDIMY);
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
            
            newMove = promptO();
            newORow = 
            newOCol = 

            //Checking that move is valid; if error, the player gets to go again
            bool hasNeighbor = isNeighborBad(board, BDIMX, BDIMY, newORow, newOCol);
            bool canFlip = isFlippable(board, BDIMX, BDIMY, newORow, newOCol);
            bool spaceFree = isSpaceFree(board, BDIMX, BDIMY, newORow, newOCol);
            
            if(!spaceFree) {
                playerOTurn = false;
                break;
            }

            //Error messages: Player O can try again
            if(!hasNeighbor) {
                cout << "Disk must be placed next to an opponent's disk." << endl;
            }
            if(!canFlip) {
                cout << "Disk must be able to flip an opponent's disk." << endl;
            } 
            

        } while(!hasNeighbor || !canFlip)
        

        }




        //Player X Protocol
        if(playerXTurn) {


        }

    }


    //Adding input to array, dissecting row and column 

    //Convert inbetween opponents (inbetweeners) 

    //Turn goes to Player O






}
























