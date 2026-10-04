#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;




int main() {
    //ifstream myFile("football.csv");
    ifstream myFile;
    myFile.open("football.csv");

    vector<vector<string>> dataset;
    string line, cell;

    //read the file row by row
    while(getline(myFile, line)){
        vector<string> row;
        stringstream ss(line);

    //split each row by commas
        while(getline(ss, cell, ',')){
            row.push_back(cell);
        }
        dataset.push_back(row);
    }

    //call the print table function
    cout<< "---Dataset Preview ---\n";
    //printTable(dataset,5,5);
    cout<<"Successfully loaded "<< dataset.size()<<" rows.\n";

    return 0;
}