////
////  q2.cpp
////  PracticeExam2016-17
////
////  Created by Olivia Gallup on 06/01/2019.
////  Copyright © 2019 Olivia Gallup. All rights reserved.
////
//
//#include <iostream>
//#include <stdlib.h>
//
//using namespace std;
//
//void printBoard(char b[3][3]) {
//    for(int i=0; i<3; i++) {
//        cout << "-------" << endl;
//        for(int j=0; j<3; j++) {
//            cout << "|" << b[i][j];
//        }
//        cout << "|" << endl;
//    }
//    cout << "-------" << endl;
//}
//bool isEmpty(char b[3][3]) {
//    bool full=true;
//    for(int i=0; i<3; i++) {
//        for(int j=0; j<3; j++) {
//            if(b[i][j] == ' ') {
//                full = false;
//                break;
//            }
//        }
//    }
//    return full;
//}
//
//int main() {
//    char c;
//    int row;
//    int col;
//    
//    char board[3][3];
//    for(int i=0; i<3; i++) {            // initializing  board
//        for(int j=0; j<3; j++) {
//            board[i][j] = ' ';
//        }
//    }
//        
//    while(!isEmpty(board)) {
//        cout << "Enter a character ('a'-'z' or 'A'-'Z'): ";
//        cin >> c;
//        cout << "Enter a row (1-3): ";
//        cin >> row;
//        row = row-1;
//        cout << "Enter a column (1-3): ";
//        cin >> col;
//        col = col-1;
//        
//        board[row][col] = c;
//        printBoard(board);
//    }
//    
//    return 0;
//}
