//
//  main.cpp
//  ProteinDatabase2
//
//  Created by Olivia Gallup on 20/11/2018.
//  Copyright © 2018 Olivia Gallup. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

struct Protein {
    int id;
    string gi;
    string ref;
    string name;
    string seq;
};

// Extracting each protein from the database individually
vector<string> extractProteins(ifstream &database) {
    cout << "Loading proteins... " << endl;
    char line[40000];           // some nubmer big enough to be larger than the char's that any individual protein would have to allocate enough memory space for each protein
    vector<string> rawProteins;
    
    database.seekg(database.beg+1);         // Start the index one char after the first > so that delimiter doesn't terminate before the first protein is recorded
    
    if(database.is_open()) {
        char currentChar;
        while(!database.eof()) {
            if(database >> currentChar) {
                
                database.getline(line, 40000, '>');
                rawProteins.push_back(line);
            }
        }
    }  else {
        cout << "Database didn't open." << endl;
    }
    
    return rawProteins;
}

// Background functions
// Protein Description
string getGi(string rawProtein) {
    //finding start and end point of gi number
    string gi;
    
    
    //TODO: cout test rawProtein.length()
//    cout<< "rawProtein string " << rawProtein << endl;
//    cout << "rawProtein.length() string size " << rawProtein.length() << endl;
    
    
    // TRY 1: manual finding of start and end index of gi to get length of gi
    int startGI =0;
    int endGI = 0;
    startGI = (rawProtein.find("gi|") + 3);
    for(int i=startGI; i<rawProtein.length(); i++) {
//        cout << "rawProtein[i] string two " << rawProtein[i] << endl;
        if(rawProtein[i] == '|') {
            endGI = i;
            break;
        }
        
    }
    
    int giLength = endGI - startGI;
    gi = rawProtein.substr(startGI, giLength);
    
    //  TODO:  cout << "gi " << gi << endl;
    return gi;
}

string getRef(string rawProtein) {
    //finding start and end point of ref number
    string ref;
    
    
    //TODO: cout test rawProtein.length()
//    cout<< "REF rawProtein string " << rawProtein << endl;
//    cout << "REF rawProtein.length() string size " << rawProtein.length() << endl;
    
    
    // TRY 1: manual finding of start and end index of ref to get length of ref
    int startRef =0;
    int endRef = 0;
    startRef = (rawProtein.find("ref|") + 4);
    for(int i=startRef; i<rawProtein.length(); i++) {
        //       TODO: cout << "rawProtein[i] string two " << rawProtein[i] << endl;
        if(rawProtein[i] == '|') {
            endRef = i;
            break;
        }
    }
    
    int refLength = endRef - startRef;
    ref = rawProtein.substr(startRef, refLength);
    
    //  TODO:  cout << "ref " << ref << endl;
    return ref;
}


string getName(string rawProtein) {
    string name;
    //TODO: cout test rawProtein.length()
//    cout<< "REF rawProtein string " << rawProtein << endl;
//    cout << "REF rawProtein.length() string size " << rawProtein.length() << endl;
    
    
    // TRY 1: manual finding of start and end index of name to get length of name
    int startName =0;
    int endName = 0;
    startName = (rawProtein.find("| ") + 2);
    for(int i=startName; i<rawProtein.length(); i++) {
        if(rawProtein[i] == '\n') {
            endName = i;
            break;
        }
    }
    
    int nameLength = endName - startName;
    name = rawProtein.substr(startName, nameLength);
    
//    cout << "name " << name << endl;
    return name;
}

string getSeq(string rawProtein) {
    string seq;
    // TRY 1: manual finding of start and end index of gi to get length of gi
    long int startSeq =0;
    startSeq = (rawProtein.find("]") + 2);
    
    seq = rawProtein.substr(startSeq);
//    cout << "seq " << seq << endl;
    return seq;
}

vector<Protein> processProteins(vector<string> rawProteins) {
    cout << "\nProcessing proteins..." << endl;
    vector<Protein> processedProteins;
    for(int i=0; i<rawProteins.size(); i++) {
        Protein currentProtein;
        currentProtein.gi = getGi(rawProteins.at(i));
        currentProtein.ref = getRef(rawProteins.at(i));
        currentProtein.id = i+1;
        currentProtein.name = getName(rawProteins.at(i));
        currentProtein.seq = getSeq(rawProteins.at(i));
        
        processedProteins.push_back(currentProtein);
        
    }
    cout << "Database loaded." << endl;
    return processedProteins;
}


// Main menu options
void overview(vector<string> rawProteins) {
    
    // TODO; protein size
    cout << "\nThe proteins in the database are from GenBank(R) \nTotal number of proteins in the database: " << rawProteins.size() << "\nAmino acids are represented by the following characters: \nA alanine \tP proline \nB aspartate/asparagine \tQ glutamine\nC cystine \tR arginine\nD aspartate \tS serine\nE glutamate \tT threonine\nF phenylalanine \tU selenocysteine\nG glycine \tV valine\nH histidine \tW tryptophan\nI isoleucine \tY tyrosine\nK lysine \tZ glutamate/glutamine\nL leucine \tX any\nM methionine \t* translation stop\nN asparagine \t- gap of indeterminate length\n\n" << endl;
}

// Search Hit Menu options
void getStats(Protein proteinFound) {
    string seq = proteinFound.seq;
    int falseAminos = (seq.size() / 70)+1;
    cout<< "\nTotal number of amino acids: " << (seq.size()-falseAminos) << endl;
    
    vector<char> aminoBois = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K','L','M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z', 'X', '*', '-'};
    
    for (int i = 0; i < aminoBois.size(); i=i+2) {
        size_t n = count(seq.begin(), seq.end(), aminoBois[i]);        //counting var's
        size_t j = count(seq.begin(), seq.end(), aminoBois[i+1]);
        cout << aminoBois[i] << ": " << n << "\t" << aminoBois[i+1] << ": " << j << endl;
        
    }
    
}


void recordProtein(Protein proteinFound, fstream &selectedProteins) {
    selectedProteins << ">gi|" << proteinFound.gi << "|ref|" << proteinFound.ref << "| PREDICTED: " << proteinFound.name << "\n" << proteinFound.seq << endl;
    cout << "The protein was written to the file.\n" << endl;
}

//Search hit menu
void searchHitMenu(Protein proteinFound, fstream &selectedProteins) {
    int action3=0;
    bool validAction = false;
    
    while(action3!= 5) {
        while(!validAction) {
            cout << "\nSelect and option from the menu below \n1) Description of the protein \n2) Protein sequence \n3) Protein statistics \n4) Record protein to file \n5) Return to main menu" << endl;
            cin >> action3;
            
            if(action3 ==0 || action3 >5) {
                cout << "Not a valid action" << endl;
            } else {
                validAction = true;
            }
        }
            
            switch (action3) {
                    // Protein Descripiton
                case 1: { validAction = false;
                    cout << "\nDescription of the protein: \nitem id: \t" << proteinFound.id << "\ngi id: \t\t " << proteinFound.gi << "\nref id: \t" << proteinFound.ref << "\nname: \t" << proteinFound.name << endl;
                    break;
                }
                case 2: validAction = false; cout << "\nProtein Seqeuence: \n" << proteinFound.seq << endl;
                    break;
                    
                case 3: validAction = false; cout << "\nReport on the protein statistics: " << endl;
                    getStats(proteinFound);
                    break;
                    
                case 4: validAction = false; recordProtein(proteinFound, selectedProteins);
                    break;
                    
                default: validAction = false;
                    break;
            }
    }
}

void findID(vector<Protein> processedProteins, fstream &selectedProteins) {
    int id=0;
    bool searchHit = false;
    while(!searchHit) {
        cout << "\nEnter an item id" << endl;
        cin >> id;
        
        if(id==0 || id> processedProteins.size()) {
            cout <<":(\nItem id not found, try again \n" << endl;
        } else {searchHit = true;}
    }
    Protein proteinFound = processedProteins.at(id-1);
    searchHitMenu(proteinFound, selectedProteins);
}

void findGI(vector<Protein> processedProteins, fstream &selectedProteins) {
    string gi;
    cout << "\nEnter gi id: " << endl;
    cin >> gi;
    
    Protein proteinFound;
    proteinFound.gi = "no";        // Initializing proteinFound so that we cacn check if a gi was created
    
    // Searching through all proteins for gi
    for(int i=0; i<processedProteins.size(); i++) {
        Protein thisProtein = processedProteins.at(i);
        if(thisProtein.gi == gi) {
            proteinFound = thisProtein;
        }
    }
    if(proteinFound.gi != "no") {
    searchHitMenu(proteinFound, selectedProteins);
    } else {
        cout << "Not a valid gi number" << endl;
    }
}

void findRef(vector<Protein> processedProteins, fstream &selectedProteins) {
    string ref;
    cout << "\nEnter ref id: " << endl;
    cin >> ref;
    
    Protein proteinFound;
    proteinFound.ref = "no";        // Initializing proteinFound so that we cacn check if a gi was created
    
    // Searching through all proteins for gi
    for(int i=0; i<processedProteins.size(); i++) {
        Protein thisProtein = processedProteins.at(i);
        if(thisProtein.ref == ref) {
            proteinFound = thisProtein;
        }
    }
    if(proteinFound.ref != "no") {
        searchHitMenu(proteinFound, selectedProteins);
    } else {
        cout << "Not a valid ref number" << endl;
    }
}

void findKeyword(vector<Protein> processedProteins, fstream &selectedProteins) {
    string keyword;
    cout << "\nEnter a keyword" << endl;
    cin >> keyword;
    
    vector<Protein> proteinsWithKeyword;    // vector that holds all the proteins found with keyword in their name
    Protein proteinFound;
    
    // Loop to search through all protein names
    for(int i=0; i<processedProteins.size(); i++) {
        Protein thisProtein = processedProteins.at(i);
        long int keywordPosition = thisProtein.name.find(keyword);
        if(keywordPosition != string::npos) {
            proteinsWithKeyword.push_back(thisProtein);
        }
    }
    
    // List of all the proteins with the keyword
    cout << "\nNumber of matches found: " << proteinsWithKeyword.size() << endl;
    for(int i=0; i<proteinsWithKeyword.size(); i++) {
        Protein thisProtein = proteinsWithKeyword.at(i);
        cout << (i+1) << ")\t" << "item id: " << thisProtein.id << ", ref id: " << thisProtein.ref << "\n\t" << thisProtein.name << endl;
    }
    
    // Selecting the protein we want
    int proteinChoice;
    cout << "\nSelect one of the matches" << endl;
    cin >> proteinChoice;
    
    for(int i=0; i<proteinsWithKeyword.size(); i++) {
        Protein thisProtein = proteinsWithKeyword.at(i);
        if(i== proteinChoice) {
            proteinFound = thisProtein;
        }
    }
    searchHitMenu(proteinFound, selectedProteins);
}





//Protein Database Selection Menu
int databaseSelectionChoice() {
    int choice = 0;
    bool promptSuccessful = false;
    
    while(!promptSuccessful) {
        cout << "\nSelect an option from the menu below \n1) Load the abridged protein data \n2) Load the complete protein data \n3) Quit database" << endl;
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


//Main manu

int mainMenu() {
    bool promptSuccessful = false;
    int action = 0;
    
    while(!promptSuccessful) {
        cout << "\nSelect an option from the menu below \n1) Overview of the database \n2) Search by protein # \n3) Search by gi # \n4) Search by ref # \n5) Search by keyword \n6) Quit database" << endl;
        cin >> action;
        if (action == 1||2||3||4||5||6) {
            promptSuccessful = true;
        }
    }
    return action;
}




int main() {
    cout<< "Welcome to the Protein Database!\n" <<endl;
    
    ifstream database;
    fstream selectedProteins("selected_proteins.txt");
    vector<string> rawProteins;
    
    
    bool databaseRunning = true;
    bool searchRunning = false;
    bool searchHit = false;
    bool validAction = false;
    
    while(databaseRunning) {
        // Action menu 1: choosing the first choices, ie loading a database or quitting
        while(!validAction) {
            int action1 = databaseSelectionChoice();
            if(action1 == 1) {
                validAction = true;
                searchRunning = true;
                database.open("protein_a.fa");
            }
            else if(action1 == 2) {
                validAction = true;
                searchRunning = true;
                database.open("protein_c.fa");
            }
            else if(action1 == 3) {
                validAction = true;
                databaseRunning = false;
            } else {
                cout << "\nNot a valid choice, choose beteen 1, 2, and 3." << endl;
            }
        }
        vector<string> rawProteins = extractProteins(database);
        vector<Protein> processedProteins = processProteins(rawProteins);
        
        if(database.is_open()) {
            while(searchRunning) {
                // Action menu 2: overview or search database, or quit
                int action2 = mainMenu();
                
                if(action2 == 1) {
                    overview(rawProteins);
                }
                if(action2 == 2) {
                    findID(processedProteins, selectedProteins);
                }
                if(action2 == 3) {
                    findGI(processedProteins, selectedProteins);
                }
                if(action2 == 4) {
                    findRef(processedProteins, selectedProteins);
                }
                if(action2 == 5) {
                    findKeyword(processedProteins, selectedProteins);
                }
                if(action2 == 6) {
                    cout << "Exiting the database... thanks for playing ;)" << endl;
                    searchRunning = false;
                    databaseRunning = false;
                }
            }
        }
        
        
        
        
    }
    
    database.close();
    return 0;
}
