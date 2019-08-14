//
// ybxx t yy y y y hy hynhy y y y y y hny hy yh y f hyf y y h y y ynhyf yh yhy y y nhyy y hy hn
//  main.cpp
//  ProteinDatabase
//
//  Created by Olivia Gallup on 11/11/2018.
//  Copyright © 2018 Olivia Gallup. All rights reserved.
//
//A  alanine               P  proline
//B  aspartate/asparagine  Q  glutamine
//C  cystine               R  arginine
//D  aspartate             S  serine
//E  glutamate             T  threonine
//F  phenylalanine         U  selenocysteine
//G  glycine               V  valine
//H  histidine             W  tryptophan
//I  isoleucine            Y  tyrosine
//K  lysine                Z  glutamate/glutamine
//L  leucine               X  any
//M  methionine            *  translation stop
//N  asparagine            -  gap of indeterminate length

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


struct protein {
    int proteinNum;
    string gi;
    string ref;
    string name;
};

vector<int> proteinsByIndex(ifstream &database) {         // Function for getting the item id of all the proteins
    vector<int> proteinIndexVector;          // Vector with the character indexes, ie positions in fstream, of each protein. size of this vector is equal to the total number of proteins in the database
    
    
// TRY 1 FAILED
//    ifstream tempDatabase = database;
//    int charIndex =0;
//
//    if(database.is_open()) {
//        // TODO: cout test database is open
//        cout << "database is open." << endl;
//
//
//
//        while(!database.eof()) {
//            char currentBoi;
//            database >> currentBoi;
//            charIndex++;
//            if (currentBoi == '>') {
//                // Number of '>'s meaning # of proteins  in database
////                cout << "current boi found at charindex: " << charIndex << endl;
//                proteinIndexVector.push_back(charIndex);
//            }
//        }
//    }
    
    
// TRY 2
    if(database.is_open()) {
        database.seekg(0, database.end);
        long int databaseLength = database.tellg();     //Gets character count in database
        database.seekg(database.beg);
        
        for(int i=0; i<databaseLength; i++) {
            database.seekg(i, database.beg);
            
            if(database.peek() == 62) {         // When the program index lands on a '>' character (062 in ASCII code), it records the protein number by storing its position in the file in a vector 'proteinIndexVector'; the index of that position in proteinIndexVector gives its protein index
                proteinIndexVector.push_back(i);
            }
        }
    }

    return proteinIndexVector;
}

// functions for finding info about protein for search key
int findGI(string searchType, string searchKey) {
    int gi;
    
    return gi;
}

int findProteinNum(string searchType, string searchKey) {
    int proteinNum;
    
    
    return proteinNum;
}

string findRef(string searchType, string searchKey, ifstream &database) {
    string ref;

    
    
    
    return ref;
}

string findName(string searchType, string searchKey) {
    string name;
    
    return name;
}

// TODO: uncomment
// Functions for finding information about a protein for action menu 3
//int findDescription(string searchType, string searchKey) {}
//
//int findSequence(string searchType, string searchKey) {
//
//}
//void recordProtein(string searchType, string searchKey) {}


protein createProtein(long int index, ifstream &database) {
//    if(searchType == "protein #") {
//        int searchKeyInt = stoi(searchKey);
//        brotein.proteinNum = searchKeyInt;          //casting string "searchkey" as an int so that gi, ref, protein number can be read as numbers in the struct datatypes
//        brotein.gi = findGI("protein #", searchKey);
//        brotein.ref = findRef("protein #", searchKey, database);
//        brotein.name = findName("protein #", searchKey);
//    } else if(searchType == "gi #") {
//        int searchKeyInt = stoi(searchKey);
//        brotein.gi = searchKeyInt;
//        brotein.proteinNum = findProteinNum("gi #", searchKey);
//        brotein.ref = findRef("gi #", searchKey);
//        brotein.name = findName("gi #", searchKey);
//    } else if(searchType == "ref #") {
//        int searchKeyInt = stoi(searchKey);
//        brotein.ref = searchKeyInt;
//        brotein.gi = findGI("ref #", searchKey);
//        brotein.proteinNum = findProteinNum("ref #", searchKey);
//        brotein.name = findName("ref #", searchKey);
//    } else if(searchType == "keyword") {
//        brotein.name = searchKey;
//        brotein.gi = findGI("ref #", searchKey);
//        brotein.proteinNum = findProteinNum("ref #", searchKey);
//        brotein.ref = findRef("ref #", searchKey);
//    }
    
    
    protein brotein;
    int charIndex =0;
    vector<char> proteinInfo;         // string for storing all char's that belong to the protein of choice, ie from > to the next > character
    
    if(database.is_open()) {
        while(!database.eof()) {
            char currentChar;
            database >> currentChar;
            charIndex++;
            if(charIndex == index) {
                do {
                    proteinInfo.push_back(currentChar);
                } while(currentChar != '>');
            }
        }
    }

    return brotein;
}


int actionsMenu1() {
    int choice = 0;
    bool promptSuccessful = false;
    
    while(!promptSuccessful) {
        cout << "Select an option from the menu below \n1) Load the abridged protein data \n2) Load the complete protein data \n3) Quit database" << endl;
        cin >> choice;
        cout << "\n";
        
        if (choice == 1 || 2|| 3) {
            promptSuccessful = true;
        } else {
            cout << "PLEASE TYPE 1, 2, OR 3" << endl;
        }
    }
    
    return choice;
}

int actionsMenu2() {
    bool promptSuccessful = false;
    int action = 0;
    
    while(!promptSuccessful) {
        cout << "Select an option from the menu below \n1) Overview of the database \n2) Search by protein # \n3) Search by gi # \n4) Search by ref # \n5) Search by keyword \n6) Quit database" << endl;
        cin >> action;
        if (action == 1||2||3||4||5||6) {
            promptSuccessful = true;
        } else {
            promptSuccessful = true;
        }
    }
    return action;
}

void overview(ifstream &database) {
    cout << "\nThe proteins in the database are from GenBank(R) \nTotal number of proteins in the database: " << proteinsByIndex(database).size() << "\nAmino acids are represented by the following characters: \nA alanine \tP proline \nB aspartate/asparagine \tQ glutamine\nC cystine \tR arginine\nD aspartate \tS serine\nE glutamate \tT threonine\nF phenylalanine \tU selenocysteine\nG glycine \tV valine\nH histidine \tW tryptophan\nI isoleucine \tY tyrosine\nK lysine \tZ glutamate/glutamine\nL leucine \tX any\nM methionine \t* translation stop\nN asparagine \t- gap of indeterminate length\n\n" << endl;

}
bool checkIfMatching(string inputKey, char currentString[inputKey.length()]) {
    bool match = true;          // See if gi typed in is a match with anything
    for(int i=0; i<inputKey.length(); i++) {
        if(currentString[i] != inputKey[i]) {
            match = false;
        } else {match = true;}
    }
    return match;
}


vector<string> search(string category, ifstream &database) {
    long int index=0;             // Stores the char position of the protein within the file
    int proteinID =  0;         // Prtoein number within database (ie its order, not char position)
    vector<int> proteinIndexVector = proteinsByIndex(database);         // Set up vector with all the protein indexes within the file in the order of appearance
    long int numberOfProteins = proteinIndexVector.size();
    
    
    // Protein # search
    if(category == "protein #") {
        bool validRequest = false;
        while(!validRequest) {
            cout << "\nEnter item id: " << endl;
            cin >> proteinID;
            
            
            //Error message
            if(proteinID < 1 || proteinID > numberOfProteins) {
                cout << "Not a valid protein ID. Try again. " << endl;
            } else {validRequest = true; }
        }
        
        // TODO: cout test proteins in vector
        for(int i=0; i<numberOfProteins; i++) {
            cout << proteinIndexVector[i] << endl;
        }
//        int first = proteinIndexVector.at(0);
//        cout << "first protein " << first << endl;
//        cout << "proteinID: " << proteinID << endl;
//
//
//        //TODO: cout test index
//        cout<< "index " << index << endl;
//
//        index = distance(proteinIndexVector.begin(), find(proteinIndexVector.begin(), proteinIndexVector.end(), proteinID));
//        //TODO: cout test index
//        cout<< "index " << index << endl;
        
        
        index = proteinIndexVector.at(proteinID-1);
        
    }
    
    // GI # Search
    else if(category == "gi #") {
        string giNum;
        cout << "\nEnter gi id: " << endl;
        cin >> giNum;
        char currentString[giNum.length()];
        bool matching = false;
        
        // cout test
        cout << "giNum.length() " << giNum.length() << endl;
        cout << "proteinIndexVector.size() " << proteinIndexVector.size() << endl;
        
        for(int proteinID=0; proteinID<proteinIndexVector.size(); proteinID++) {
            for(int i=0; i<giNum.length(); i++) {      // Again, index stores the char position of the protein within the file
                database.seekg((proteinIndexVector.at(proteinID)+4+i), database.beg);        // index+4 puts the index at the start of the gi number
                //cout << "current pos " << database.tellg() << endl;
                currentString[i] = database.peek();
            }
            matching = checkIfMatching(giNum, currentString);
            if(matching) {
                index = proteinIndexVector.at(proteinID);
            }
        }
        if(index==0) {
            cout << "No matching gi number found." << endl;
            
        }
        
        
    } else if(category == "ref #") {
        string refNum;
        cout << "\nEnter ref id: " << endl;
        cin >> refNum;
        char currentString[refNum.length()];
        bool matching = false;
        
        for(int proteinID=0; proteinID < proteinIndexVector.size(); proteinID++) {
            for(int i=0; i<refNum.length(); i++) {      // Again, index stores the char position of the protein within the file
                database.seekg((proteinIndexVector.at(proteinID)+4+i), database.beg);        // index+4 puts the index at the start of the gi number
                //cout << "current pos " << database.tellg() << endl;
                currentString[i] = database.peek();
            }
            matching = checkIfMatching(refNum, currentString);
            if(matching) {
                index = proteinIndexVector.at(proteinID);
            }
        }
        if(index==0) { cout << "No matching gi number found." << endl;}
        
    } else if(category == "keyword") {
        
    } else {
        cout << "Not a valid search key, try again. " << endl;
    }
    
    createProtein(index, database);
    
}




int main() {
    bool databaseRunning = true;    // This means program is running, set to false when user wants to quit
    bool searchRunning = false;     // This is so the user can keep searching for things until they decide to quit
    cout << "Welcome to the Protein Database!\n" << endl;
    ifstream database;
    
    while(databaseRunning) {
        // Action menu 1: choosing the first choices, ie loading a database or quitting
        int action1 = actionsMenu1();
        
        if(action1 == 1) {
            searchRunning = true;
            database.open("protein_a.fa");
            cout << "Loading database..." << endl;
        }
        if(action1 == 2) {
            searchRunning = true;
            database.open("protein_c.fa");
            cout << "Loading database..." << endl;
        }
        if(action1 == 3) {
            databaseRunning = false;
        }
        // TODO: cout test
        vector<int> proteinIndexVector = proteinsByIndex(database);
        cout << "amount of proteins: " << proteinIndexVector.size() << endl;
        vector<int> proteinIndexVector2 = proteinsByIndex(database);
        cout << "amount of proteins: " << proteinIndexVector2.size() << endl;
        
        while(searchRunning) {
            // Action menu 2: overview or search database, or quit
            int action2 = actionsMenu2();

            if(action2 == 1) {
                overview(database);
            }
            if(action2 == 2) {
                search("protein #", database);
            }
            if(action2 == 3) {
                search("gi #", database);
            }
            if(action2 == 4) {
                search("ref #", database);
            }
            if(action2 == 5) {
                search("keyword", database);
            }
            if(action2 == 6) {
                searchRunning = false;
                databaseRunning = false;
            }
        }
        
        
        
    
    }
}
