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

    map<short, vector<FlightEdge>> graph;

    int V;
    int E;

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

    map<string, short> WAC;
    map<string, string> airlines;

};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTGRAPH_H
