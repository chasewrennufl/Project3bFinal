//
// Created by Chase Wrenn on 7/22/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H

#include <string>
#include "FlightEdge.h"
#include <map>
#include <vector>

using namespace std;

struct FlightGraph
{
public:

    map<short, vector<FlightEdge>> graph; //adjacency list

    int V; //# of vertices
    int E; //# of edges

    FlightGraph(); 

    void insertFlightEdge(FlightEdge& e);
    bool isFlight(FlightEdge& e);
    bool isFlight(short src, short dest);
    double getPrice(string src, string dest);
    vector<FlightEdge> getFlightsFromLoc(short src);
    void printGraph();

    string getAirlineFromCode(string code);
    string getAirlineFromData(short src, short dest, double price);
    double getWeight(short src, short dest);
    string getLocFromAC(short AC);
    short getACfromLoc(string loc);
    string routeText(vector<FlightEdge> route);

    map<string, short> WAC; //map from a location to that locations WAC (world area code)
    map<string, string> airlines; //map from code of airline (keys i.e. "AA") to airline (values) (i.e. American Airline)

};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
