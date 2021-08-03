#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H

#include "iostream"

struct FlightEdge
{

    short quarter;

    //Using area codes from data to minimize storage
    short originWAC; //code for origin location
    short destWAC; //code for destination location


    std::string airlineCode; //two letter code for airline
    double price;
};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H
