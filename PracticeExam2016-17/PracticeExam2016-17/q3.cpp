//
//  q3.cpp
//  PracticeExam2016-17
//
//  Created by Olivia Gallup on 07/01/2019.
//  Copyright © 2019 Olivia Gallup. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

void print1(vector<int> v) {
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++) {
        cout<< *it << endl;
    }
}
template <typename T>
void print2(vector<T> v) {
    for(typename vector<T>::iterator it=v.begin(); it!=v.end(); it++) {
        cout<< *it << endl;
    }
}

int main() {
    //Part 1
//    vector<int> vint;
//    vint.push_back(3);
//    vint.push_back(1);
//    vint.push_back(4);
//    cout << "Part A" << endl;
//    print1(vint);
    
    
    //Part 2
    vector<int> vint;
    vector<char> vchar;
    vector<double> vdouble;
    vint.push_back(3);
    vint.push_back(1);
    vint.push_back(4);
    vchar.push_back('p');
    vchar.push_back('i');
    vdouble.push_back(3.14);
    vdouble.push_back(2.71);
    cout << "Part B" << endl;
    print2(vint);
    print2(vchar);
    print2(vdouble);
}
