#ifndef PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#define PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#include <vector>
#include "FlightGraph.h" - need to rearrange paths


class DjikstrasModAlgo {
private:
    map<short, double> d; //keys are the WACs of the locations, values are the price to get to location from source

    map<short, short> p; //keys are WACs of locations, values are prev node in cheapest path from src

    vector<FlightEdge> route;

    double DBL_MAX = std::numeric_limits<double>::max();

    short minDistance(FlightGraph* g, map<short, bool> reached); //finds the next vertex to check within Dijkstra's 
                                                                 // finds vertex not already checked with the smallest value in the map d


public:

    void djikstra(FlightGraph* g, short source);

    vector<FlightEdge> calculateRoute(FlightGraph *g, short source, vector<short> dest);

    vector<FlightEdge> getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool>& reached);

};


#endif //PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
