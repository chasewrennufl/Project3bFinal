//
// Created by Chase Wrenn on 7/27/21.
//

#ifndef PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#define PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
#include <vector>
#include "FlightGraph.h" - need to rearrange paths


class DjikstrasModAlgo {
private:
    map<short, double> d;

    map<short, short> p;

    vector<FlightEdge> route;

    double DBL_MAX = std::numeric_limits<double>::max();

    short minDistance(FlightGraph* g, map<short, bool> reached);


public:

    void djikstra(FlightGraph* g, short source);

    vector<FlightEdge> calculateRoute(FlightGraph *g, short source, vector<short> dest);

    vector<FlightEdge> getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool>& reached);

};


#endif //PROJECT3_TRAVEL_OPTIMIZATION_DJIKSTRASMODALGO_H
