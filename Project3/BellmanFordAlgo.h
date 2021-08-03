#ifndef PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H
#define PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H

#include "FlightGraph.h"
class BellmanFordAlgo {
private:

    map<short, double> d; //keys are the WACs of the locations, values are the price to get to location from source

    map<short, short> p; //keys are WACs of locations, values are prev node in cheapest path from src

    vector<FlightEdge> route;

    double DBL_MAX = std::numeric_limits<double>::max();

public:

    void bellmanFord(FlightGraph* g, short source); //within calculateRoute

    vector<FlightEdge> calculateRoute(FlightGraph* g, short source, vector<short> dest);

    vector<FlightEdge> getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool>& reached);



};


#endif //PROJECT3_TRAVEL_OPTIMIZATION_BELLMANFORDALGO_H
