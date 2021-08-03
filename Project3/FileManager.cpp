#include <vector>
#include <iostream>
#include <sstream>
#include "FileManager.h"

void FileManager::buildGraph(string fileName, short q,  map<string, bool> airlines, FlightGraph& fgraph) {
    
    fstream fin;
    
    fin.open(fileName, ios::in);
    
    if(!fin.is_open()) 
        throw std::runtime_error("Could not open file");
    
    short quarter, srcWAC, destWAC;
    string airlineCode;
    double price;
    
    vector<string> row;
    string line, temp, data;
    cout << "Loading Flight Data..." << endl;
    fin >> temp;  //need this to remove header line
    bool pastQ = false; //since data ordered by q, can skip rest of data once past our q
    
    while (fin >> line && !pastQ)
    {
        row.clear();
        stringstream s(line);

        while (getline(s, data, ',')) //grab our ata
        {
            row.push_back(data);
        }
        
        FlightEdge e;
        e.quarter = stoi(row[4]);
        e.originWAC = stoi(row[6]);
        e.destWAC = stoi(row[8]);
        e.airlineCode = row[12];
        e.price = stod(row[13]);
       
        if (e.quarter == q && airlines.find(e.airlineCode) != airlines.end()) { //check to make sure right q and airline
            fgraph.insertFlightEdge(e);
        }
        else if (e.quarter > q) {
            pastQ = true; //Will skip over the rest of the data
        }
        
    }
    cout << "Flight Data loaded successfully!" << endl;
    
}
