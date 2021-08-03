//
// Created by Chase Wrenn on 7/22/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H
#define PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H

#include "iostream"

struct FlightEdge
{

    short quarter;

    //Using area codes from data to minimize storage
    short originWAC;
    short destWAC;


    std::string airlineCode;
    double price;
};

#endif //PROJECT3_TRAVEL_OPTIMIZATION_FLIGHTEDGE_H
