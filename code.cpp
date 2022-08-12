#include "InventoryItem.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void hCommand(){
    cout << "Supported commands:" << endl;
    cout << "        a     "  << "Add parts." << endl;
    cout << "        h     "  << "print help text." << endl;
    cout << "        i     "  << "Input inventory data from a file." << endl;
    cout << "        n     "  << "New inventory Item." << endl;
    cout << "        o     "  << "Output inventory data to a file." << endl;
    cout << "        p     "  << "Print inventory list." << endl;
    cout << "        q     "  << "quit (end the program)." << endl;
    cout << "        r     "  << "Remove parts." << endl;
}

// gets necesarry info from each line
void  splitLineToArray(string inputFileName, string splitter, string fieldArray[]){
    int splitterIndex, beginIndex = 0,fieldCount = 0;            // stores splitter position
    string lineContent;       // field data
    bool endOfLine = false;   // makes sure line isnt over

    while (!endOfLine){
        // index of where string is split
        splitterIndex = inputFileName.find(splitter, beginIndex);

        if (splitterIndex >= 0){
            lineContent = inputFileName.substr(beginIndex, splitterIndex - beginIndex);
            fieldCount++;
            beginIndex = splitterIndex + 1;
        }else{
            endOfLine = true;
            splitterIndex = inputFileName.length();
            
            if (splitterIndex > beginIndex){
                lineContent = inputFileName.substr(beginIndex, splitterIndex - beginIndex);
                fieldCount++;
            }
            
        }
        
        fieldArray[fieldCount - 1] = lineContent;
    }
}


// Add parts: DONE
void aCommand(InventoryItem inventory[]) {
    int itemIndex, totalAmt, newTotalAmt;

    cout << "Choose a Item Number: ";
    cin >> itemIndex;
    
    cout << "How many parts to add? ";
    cin >> totalAmt;
    newTotalAmt = inventory[itemIndex].getUnits() + totalAmt;
    
    if (newTotalAmt >= 31){
        cout << "Error: You cannot hold more than 30 parts.";
    }
    else{
        inventory[itemIndex].setUnits(newTotalAmt);
    }
}
// Input inventory data from a file: DONE
void iCommand(InventoryItem inventory[], int &size, ifstream &inputFile, string arr[]) {
    string filename, inputFileName;
    int record = 0;

    cout << "Enter name of input file: ";
    cin >> filename;
    inputFile.open(filename);

    while (getline(inputFile, inputFileName)) {
        splitLineToArray(inputFileName, "|", arr);
        string trav = arr[1];
        
        double itemCost = stod(arr[2], NULL);
        
        int itemAmt = stoi(arr[3], NULL);
        
        inventory[size].setDescription(trav);
        inventory[size].setCost(itemCost);
        inventory[size].setUnits(itemAmt);
        
        size++;
        record++;
    }

    cout << record << " records loaded to array." << endl;
    inputFile.close();
}

// prints inventory content
void pCommand(InventoryItem inventory[], int &size) {
    cout << setw(5) << right << "Item Num" << left << setw(37) << "     Description"
        << setw(13) << right << "Cost" << setw(13) << "totalAmt" << endl;
    cout << setw(5) << right << "________" << left << setw(37) << "     ___________"
        << setw(13) << right << "____" << setw(13) << "________" << endl;

    int x = 0;
    
    while(x < size){
        cout << setw(5) << right << x << "        " << left << setw(40) << inventory[x].getDescription() << setw(5) << right << fixed << setprecision(2) << inventory[x].getCost()
            << setw(13) << right << inventory[x].getUnits() << endl;
        
        x++;
    }
    cout << size << " records." << endl;
}

// create new inentory item
void nCommand(InventoryItem inventory[], int &size) {
    string itemDesc;
    double itemCost;
    int itemAmt;

    cout << "Enter description for new Item: ";
    getline(cin, itemDesc);
    inventory[size - 1].setDescription(itemDesc);

    cout << "Enter unit cost for new Item: ";
    cin >> itemCost;
    inventory[size - 1].setCost(itemCost);

    cout << "Enter initial totalAmt for the new Item: ";
    cin >> itemAmt;
    if (itemAmt < 0 || itemAmt > 30){
        cout << "ERROR: initial totalAmt must be >= zero and <= 30.";
    }else {
        inventory[size - 1].setUnits(itemAmt);
        cout << "Announcing a new inventory Item: " << itemDesc << endl;
        cout << "We now have " << size << " different inventory Items in stock!" << endl;
    }
}

// print inventory content to a output file
void oCommand(ofstream &outputFile, InventoryItem inventory[], int &size) {
    string fileName;

    cout << "Enter name of output file: ";
    getline(cin >> ws, fileName);
    
    outputFile.open(fileName);

    for (int i = 0; i < size; i++) {
        outputFile << i << '|' << inventory[i].getDescription() << '|' << inventory[i].getCost() << '|'
        << inventory[i].getUnits() << endl;
    }

    cout << size << " records written to file." << endl;
    outputFile.close();
}
// remove inventory item
void rCommand(InventoryItem inventory[]) {
    int itemIndex, totalAmt;
    int newTotalAmt;

    cout << "Choose a Item Number: ";
    cin >> itemIndex;
    cout << "How many parts to remove? ";
    cin >> totalAmt;

    newTotalAmt = inventory[itemIndex].getUnits() - totalAmt;
    if (newTotalAmt < 0){
        cout << "Error: You are attemping to remove more parts than the Item currently holds.";
    }else{
        inventory[itemIndex].setUnits(newTotalAmt);
    
    }
}


int main() {
    int inventorySize = 0;
    string userChoice;
    bool checked = true;
    
    ifstream inputFile;
    ofstream outputFile;
    
    string array[200];
    InventoryItem inventory[100];

    while (true) {
        cout << "Command: ";
        cin >> userChoice;
        cin.ignore();
        
        if(userChoice == "a"){
            aCommand(inventory);
        }
        if(userChoice == "h"){
            hCommand();

        }
        if(userChoice == "i"){
            iCommand(inventory, inventorySize, inputFile, array);

        }
        if(userChoice == "p"){
            pCommand(inventory, inventorySize);
            
        }
        if(userChoice == "n"){
            inventorySize++;
            nCommand(inventory, inventorySize);

        }
        if(userChoice == "o"){
            oCommand(outputFile, inventory, inventorySize);
        }
        if(userChoice == "q"){
            checked = false;
        }
        if(userChoice == "r"){
            rCommand(inventory);
        }
        
        
        
    }
    return 0;
}
