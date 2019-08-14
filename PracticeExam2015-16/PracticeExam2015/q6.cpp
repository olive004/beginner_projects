////
////  q6.cpp
////  PracticeExam2019
////
////  Created by Olivia Gallup on 06/01/2019.
////  Copyright © 2019 Olivia Gallup. All rights reserved.
////
//
//
//#include <iostream>
//#include <iomanip>
//#include <math.h>
//#include <stdio.h>
//
//using namespace std;
//
//
//class Shape {
//public:
//    float x;
//    float y;
//    
//    Shape() {
//        cout << setprecision(3);
//        x=0;
//        y=0;
//    }
//    Shape(const float x_in, const float y_in) {
//        cout << setprecision(3);
//        x =x_in;
//        y =x_in;
//    }
//    virtual int getArea() {
//        return 0;
//    }
//    virtual float getPerimeter() {
//        return 0;
//    }
//    
//};
//
//class Rectangle : public Shape {
//private:
//    float w;
//    float h;
//    
//public:
//    Rectangle(float x_in, float y_in, float w_in, float h_in) {
//        x =x_in;
//        y =y_in;
//        w =w_in;
//        h = h_in;
//    }
//    int getArea() {
//        return (w*h);
//    }
//    float getPerimeter() {
//        return (2*w + 2*h);
//    }
//};
//
//class Circle : public Shape {
//private:
//    float r;
//    
//public:
//    Circle(float x_in, float y_in, float r_in) {
//        x =x_in;
//        y =y_in;
//        r =r_in;
//    }
//    int getArea() {
//        int area = (M_PI*r*r);
//        return area;
//    }
//    float getPerimeter() {
//        float perimeter =(2*M_PI*r);
//        return perimeter;
//    }
//};
//
//
//int main() {
//    Shape* p_shape;
//    Rectangle shape1(1,2,15,10);
//    Circle shape2(3,2,10);
//    
//    cout<< "shape 1 area: " << shape1.getArea() <<endl;
//    cout<< "shape 1 perimeter: " << shape1.getPerimeter() <<endl;
//    cout<< "shape 2 area: " << shape2.getArea() <<endl;
//    cout<< "shape 2 perimeter: " << shape2.getPerimeter() <<endl;
//    p_shape = &shape1;
//    cout<< "shape 1 area: " << p_shape->getArea() <<endl;
//    cout<< "shape 1 perimeter: " << p_shape->getPerimeter() <<endl;
//    p_shape = &shape2;
//    cout<< "shape 2 area: " << p_shape->getArea() <<endl;
//    cout<< "shape 2 perimeter: " << p_shape->getPerimeter() <<endl;
//    return 0;
//}
