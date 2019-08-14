////
////  q4.cpp
////  PracticeExam2019
////
////  Created by Olivia Gallup on 06/01/2019.
////  Copyright © 2019 Olivia Gallup. All rights reserved.
//
//
//
//#include <iostream>
//#include <stdio.h>
//
//using namespace std;
//
//template <typename T>
//class Database
//{
//private:
//    string name;
//    int id;
//    T val;
//public:
//    Database() {
//        id = 0;
//        val = 0;
//    }
//    Database(string name_in, int id_in, T val_in) {
//        name = name_in;
//        id = id_in;
//        val = val_in;
//    }
//    void setName(string name_in){
//        name = name_in;
//    }
//    void setID(int id_in) {
//        id = id_in;
//    }
//    void setVal(T val_in) {
//        val = val_in;
//    }
//    string getName() {
//        return name;
//    }
//    int getID() {
//        return id;
//    }
//    T getVal() {
//        return val;
//    }
//    void print() {
//        cout<<"Name: "<< getName()<<", ID: "<< getID() <<", val: "<< getVal() <<endl;
//    }
//};
//
//int main()
//{
//    Database<int> data1;
//    Database<int> data2("triangle", 15, 68);
//    Database<double> data3("square", 12, 12.7123);
//    data1.print();
//    data2.print();
//    data3.print();
//    data1.setName("circle");
//    data1.setID(3);
//    data1.setVal(12);
//    data1.print();
//    data2.print();
//    data3.print();
//    cout<<"Name: "<<data3.getName()<<", ID: "<< data3.getID()
//    <<", val: "<<data3.getVal()<<endl;
//    return 0;
//}
