//
// Created by Chase Wrenn on 7/27/21.
//

#include "DjikstrasModAlgo.h"


void DjikstrasModAlgo::djikstra(FlightGraph* g, short source) {
    map<short, bool> reached;

    for (auto itr = g->graph.begin(); itr != g->graph.end(); itr++) {
        d[itr->first] = DBL_MAX;
        p[itr->first] = 0;
        reached[itr->first] = false;
    }
    d[source] = 0;

    bool allReached = false;
    while (!allReached) {
        short u = minDistance(g, reached);
        reached[u] = true;
        vector<FlightEdge> cur = g->graph[u];
        for (int i = 0; i < cur.size(); i++) {
            double temp = d[u] + cur.at(i).price;
            if (temp < d[cur.at(i).destWAC]) {
                d[cur.at(i).destWAC] = temp;
                p[cur.at(i).destWAC] = u;
            }
        }
        allReached = true;
        for (auto itr = reached.begin(); itr != reached.end() && allReached; itr++) {
            allReached = itr->second;
        }
    }
}

vector<FlightEdge> DjikstrasModAlgo::calculateRoute(FlightGraph *g, short source, vector<short> dest) {
    map<short, bool> reached; //tracks reached destinations
    short src = source; //tracks current source
    vector<FlightEdge> result; //resulting vector in order
    //for each destination, map pair created with bool false to show location has not been reached
    for (int i = 0; i < dest.size(); i++) {
        reached.insert(make_pair(dest.at(i), false));
    }
    bool fin = false; //tracks if all dest have been reached
    while (!fin) {
        fin = true; //set to true;
        double min = DBL_MAX;
        short end = 0;
        djikstra(g, src); //finds paths to all nodes
        for (auto itr = d.begin(); itr != d.end(); itr++) {
            auto destSet = reached.find(itr->first);
            if (destSet != reached.end()) {
                if (itr->second < min &&  !destSet->second) { //sets destination to minimum remaining destination
                    min = itr->second;
                    end = itr->first;
                }
            }
        }
        vector<FlightEdge> cur = getCurrentPath(g, src, end, reached); //backtracks through d and p maps to create path
        //WORKS TO HERE
        for (int i = cur.size()-1; i >= 0; i--) { //go through backtrack backwards for correct order
            result.push_back(cur.at(i));
        }
        for (auto itr = reached.begin(); itr != reached.end() && fin; itr++) { //check all dest have been reached
            fin = itr->second;
        }
        src = result.at(result.size()-1).destWAC;
    }
    short finalDest = result.at(result.size()-1).destWAC;
    map<short, bool> hold;
    hold.insert(make_pair(source, false));
    djikstra(g, finalDest);
    vector<FlightEdge> returnPath = getCurrentPath(g, finalDest, source, hold); //return back to original source
    for (int i = returnPath.size()-1; i >= 0; i--) {
        result.push_back(returnPath.at(i));
    }
    return result; //return total path
}

vector<FlightEdge> DjikstrasModAlgo::getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool> &reached) {
    short cur = dest;
    vector<FlightEdge> path;
    while (cur != src) {
        reached[cur] = true;
        short last = p[cur];
        FlightEdge edge;
        edge.price = d[cur] - d[last];
        edge.destWAC = cur;
        edge.originWAC = last;
        edge.airlineCode = g->getAirlineFromData(edge.originWAC,edge.destWAC, edge.price);
        path.push_back(edge);
        cur = last;
    }
    return path;
}

short DjikstrasModAlgo::minDistance(FlightGraph* g, map<short, bool> reached) {

    // Initialize min value
    double min = DBL_MAX;
    short closest;

    for (auto itr = reached.begin(); itr != reached.end(); itr++)
        if (!itr->second && d[itr->first] <= min)
            min = d[itr->first], closest = itr->first;

    return closest;
}
