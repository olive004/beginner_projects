//
//  main.cpp
//  fitting_earrings_on_sheet
//
//  Created by Olivia Gallup on 30/03/2019.
//  Copyright © 2019 Olivia Gallup. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

// See the matlab file of similar name for an optimized version of this code (also from 30/03/2019)

// Functions
int getSheetWidth() {
    int sheetWidth;
    cout << "Width: " << endl;
    cin >> sheetWidth;
    
    return sheetWidth;
}
int getSheetHeight() {
    int sheetHeight;
    cout << "Height: " << endl;
    cin >> sheetHeight;
    
    return sheetHeight;
}

int getItemWidth() {
    int itemWidth;
    cout << "Width: " << endl;
    cin >> itemWidth;
    
    return itemWidth;
}
int getItemHeight() {
    int itemHeight;
    cout << "Height: " << endl;
    cin >> itemHeight;
    
    return itemHeight;
}
void displayMargin(float marginW, float marginH) {
    cout << "Margin horizontally (by width, mm): " << marginW << endl;
    cout << "Margin vertically (by height, mm): " << marginH << endl;
}
bool getDefaultStatus() {
    char defaultStatus;
    bool correctChar = false;
    bool isDefault = false;
    while(!correctChar) {
        cout << "Is the sheet size default, ie 425mm width, 305mm height? (y/n)" << endl;
        cin >> defaultStatus;
        if(defaultStatus == 'y') {
            isDefault = true;
            correctChar = true;
        }
    }
    return isDefault;
}

float getMaterialCost() {
    float cost;
    cout << "What is the cost per square meter of the material?" << endl;
    cin >> cost;
    
    return cost;
}

int main() {
    
    bool isDefault = getDefaultStatus();
    bool isSwappable = false;
    
    float sheetWidth;
    float sheetHeight;
    float itemWidth;
    float itemHeight;
    
    
    if(isDefault) {
        sheetHeight = 305;
        sheetWidth = 425;
        
    } else {
        cout << "Enter sheet dimensions (mm)" << endl;
        sheetWidth = getSheetWidth();
        sheetHeight = getSheetHeight();
    }
    
    cout << "Dimensions of item to cut (mm)" << endl;
    itemWidth = getItemWidth();
    itemHeight = getItemHeight();
    
    
    float numItems = (floor(sheetWidth/itemWidth))*(floor(sheetHeight/itemHeight));
    float numItemsSwappedWH = (floor(sheetHeight/itemWidth))*(floor(sheetWidth/itemHeight));
    
    
    // ITEM COUNT
    
    if(numItems < numItemsSwappedWH) {
        isSwappable = true;
    }
    if(isSwappable) {
        cout << "Rotate the item by 90deg." << endl;
        cout << "Number of items cuttable: " << numItemsSwappedWH << endl;
        float marginW = (sheetWidth/itemWidth) - floor(sheetWidth/itemWidth);
        float marginH = (sheetHeight/itemHeight) - floor(sheetHeight/itemHeight);
        displayMargin(marginW, marginH);
    } else {
        cout << "Don't rotate the item by 90deg." << endl;
        cout << "Number of items cuttable: " << numItems << endl;
        float marginW = (sheetWidth/itemWidth) - floor(sheetWidth/itemWidth);
        float marginH = (sheetHeight/itemHeight) - floor(sheetHeight/itemHeight);
        displayMargin(marginW, marginH);
    }
    
    // COST
    
    cout << endl;
    float costPerM = getMaterialCost();     // cost per meter squared of material
    
    float costPerItem = (costPerM)/(1000*1000) * (itemHeight*itemWidth);       // cost of item per area (m^2); cost per meter squared in m converting to cost per meter square in mm times the item area
    
    cout << "Each item will cost " << costPerItem << "£" << endl;
    
    
    return 0;
}
