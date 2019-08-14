//
//  q4.cpp
//  PracticeExam2016-17
//
//  Created by Olivia Gallup on 07/01/2019.
//  Copyright © 2019 Olivia Gallup. All rights reserved.
//

#include <stdlib.h>
#include <iostream>

using namespace std;

class Rectangle {
private:
    double x;
    double y;
    double w;
    double h;
public:
    Rectangle(){
        x=0;
        y=0;
        w=0;
        h=0;
    }
    Rectangle(double x_in, double y_in, double w_in,double h_in) {
        x=x_in;
        y=y_in;
        w=w_in;
        h=h_in;
    }
    double area(){
        return (w*h);
    }
    double perimeter(){
        return (2*w+2*h);
    }
};
class Circle {
private:
    double x;
    double y;
    double r
public:
    Circle(){
        x=0;
        y=0;
        w=0;
        h=0;
    }
    Circle(double x_in, double y_in, double r_in) {
        x=x_in;
        y=y_in;
        r=r_in;
    }
    double area(){
        return (3.14*r*r);
    }
    double perimeter(){
        return (2*3.14*r);
    }
};

int main(){
    Rectangle r0;
    Rectangle r1(0,0,2,5); // the order is x, y, w, h
    Circle c0;
    Circle c1(0,0,4); // the order is x, y, r
    cout << "Part A." << endl;
    cout << "area: " << r0.area() << endl;
    cout << "perimeter: " << r0.perimeter() << endl;
    cout << "area: " << r1.area() << endl;
    cout << "perimeter: " << r1.perimeter() << endl;
    cout << "area: " << c0.area() << endl;
    cout << "perimeter: " << c0.perimeter() << endl;
    cout << "area: " << c1.area() << endl;
    cout << "perimeter: " << c1.perimeter() << endl;
}
