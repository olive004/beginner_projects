#include <iostream>
using namespace std;

#define BDIMX 6         //board dim of rows
#define BDIMY 6         //board dimension of columns

//Reversi game 6x6 
//Functions

//Prompt functions
int promptUser1Row() {
    int xRow;
    bool invalidMove;
    
    cout << "Player 1: Give me a row for your x!" << endl;
    cin >> xRow >> endl;

    return xRow;
}
int promptUser1Col() {
    int XCol;

    cout << "Player 1: Now give me a column for your x!" << endl;
    cin >> xCol >> endl;

    return xCol;
}
int promptUser2Row() {
    int xRow;
    
    cout << "Player 2: Give me a row for your x!" << endl;
    cin >> xRow >> endl;

    return xRow;
}
int promptUser2Col() {
    int XCol;

    cout << "Player 2: Now give me a column for your x!" << endl;
    cin >> xCol >> endl;

    return xCol;
}









int main() {

char board[BDIMX][BDIMY];
char userInput;

//Fill board
for(int i=0;i<BDIMX; i++) {
    for(int j=0;j<BDIMY; j++) {
        board[i][j] = ' ';
    }
}

int gameOver = 0;

//Create board before the game starts
refreshBoard(board[0][0]);

//Declaring relevant vars
bool spaceIsNotFree;    //reflects if the position to be filled is in fact free
int xRow, xCol;
int oRow, oCol;         //column and row for the latest move of player x and player o

while(!gameOver) {

    //Player 1
    xRow = promptUser1Row();
    xCol = promptUser1Col();

    //checking that space is free
    if(board[xRow][xCol] == ' ') {
        spaceIsNotFree = false;
    } else spaceIsNotFree = true;

    while(spaceIsNotFree) {
        cout << "Oh no, that space has been occupied already!" << endl;
        xRow = promptUser1Row();
        xCol = promptUser1Col();
    }

    board[xRow][xCol] = 'x';
    //Swapping sequence

    if(board[xRow+1][xCol] == 'o' && board[xRow+2][xCol] == 'x') board[xRow+1][xCol] = 'x';
    else if(board[xRow-1][xCol] == 'o' && board[xRow-2][xCol] == 'x') board[xRow-1][xCol] = 'x';
    else if(board[xRow][xCol+1] == 'o' && board[xRow][xCol+2] == 'x') board[xRow][xCol+1] = 'x';
    else if(board[xRow][xCol-1] == 'o' && board[xRow][xCol-2] == 'x') board[xRow][xCol-1] = 'x';
    
    //Refresh sequence
    for(int i=0; i<BDIMX; i++) {
        for(int j=0; j<BDIMY; j++) {
            cout << "------"
        }
    }


    //Player 2
    cout << "Now it's time for Player 2 :3" << endl;
    oRow = promptUser2Row();
    oCol = promptUser2Col();

    //checking that space is free
    if(board[oRow][oCol] == ' ') {
        spaceIsNotFree = false;
    } else spaceIsNotFree = true;
    

    while(spaceIsNotFree) {
        cout << "Oh no, that space has been occupied already!" << endl;
        oRow = promptUser2Row();
        oCol = promptUser2Col();
    }

    board[oRow][oCol] = 'o';
    if(checkIfSwappable(oRow, oCol)) {
        swapPiece();
    }

    refreshBoardO(oRow, oCol);

}





}



