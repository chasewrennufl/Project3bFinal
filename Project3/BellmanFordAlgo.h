//
// Created by Chase Wrenn on 7/31/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H
#define PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H

#include "FlightGraph.h"
class BellmanFordAlgo {
private:

    map<short, double> d;

    map<short, short> p;

    vector<FlightEdge> route;

    double DBL_MAX = std::numeric_limits<double>::max();

public:

    void bellmanFord(FlightGraph* g, short source);

    vector<FlightEdge> calculateRoute(FlightGraph* g, short source, vector<short> dest);

    vector<FlightEdge> getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool>& reached);



};


#endif //PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H
