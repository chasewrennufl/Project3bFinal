#include "DjikstrasModAlgo.h"


void DjikstrasModAlgo::djikstra(FlightGraph* g, short source) {
    map<short, bool> reached; //this is to help not go to repeat vertices

    for (auto itr = g->graph.begin(); itr != g->graph.end(); itr++) { //for all vertices
        d[itr->first] = DBL_MAX; //assigning our d and b and reached
        p[itr->first] = 0;
        reached[itr->first] = false;
    }
    d[source] = 0; //initialize source

    bool allReached = false;
    while (!allReached) { //while we haven't reached all nodes
        short u = minDistance(g, reached); //find the minimum d to evaluate the next node as origin;
        reached[u] = true; //add it to reached
        vector<FlightEdge> cur = g->graph[u]; //set cur to all edges with u as its origin
        for (int i = 0; i < cur.size(); i++) { //for all edges with u as origin
            double temp = d[u] + cur.at(i).price; //Relaxtion right here and below
            if (temp < d[cur.at(i).destWAC]) {
                d[cur.at(i).destWAC] = temp;
                p[cur.at(i).destWAC] = u;
            }
        } //Below simply checks if all verticies were checked or not
        allReached = true;
        for (auto itr = reached.begin(); itr != reached.end() && allReached; itr++) { //for all vertices
            allReached = itr->second; //if one is false (aka not checked), this will continue the loop
        }
    }
}

vector<FlightEdge> DjikstrasModAlgo::calculateRoute(FlightGraph *g, short source, vector<short> dest) {
    map<short, bool> reached; //tracks reached destinations
    short src = source; //tracks current source
    vector<FlightEdge> result; //resulting vector in order
    //for each destination, map pair created with bool false to show location has not been reached
    for (int i = 0; i < dest.size(); i++) {
        reached.insert(make_pair(dest.at(i), false));  //set up our checks
    }
    bool fin = false; //tracks if all dest have been reached
    while (!fin) { //while we have not reached all destinations
        fin = true; //set to true;
        double min = DBL_MAX;
        short end = 0;
        djikstra(g, src); //finds paths to all nodes
        for (auto itr = d.begin(); itr != d.end(); itr++) { //for all nodes
            auto destSet = reached.find(itr->first); //find out destination
            if (destSet != reached.end()) {
                if (itr->second < min &&  !destSet->second) { //sets destination to minimum remaining destination
                    min = itr->second;
                    end = itr->first;
                }
            }
        }
        vector<FlightEdge> cur = getCurrentPath(g, src, end, reached); //backtracks through d and p maps to create path for minimum

        for (int i = cur.size()-1; i >= 0; i--) { //go through backtrack backwards for correct order
            result.push_back(cur.at(i));
        }
        for (auto itr = reached.begin(); itr != reached.end() && fin; itr++) { //check all dest have been reached
            fin = itr->second;
        }
        src = result.at(result.size()-1).destWAC; //assigns new source
    }
    short finalDest = result.at(result.size()-1).destWAC; //to get round trip, need to set last destination as one to origin
    map<short, bool> hold;
    hold.insert(make_pair(source, false));
    djikstra(g, finalDest); //run dijkstra one last time
    vector<FlightEdge> returnPath = getCurrentPath(g, finalDest, source, hold); //return back to original source
    for (int i = returnPath.size()-1; i >= 0; i--) {
        result.push_back(returnPath.at(i)); //pushes the total path to the vector<FlightEdge>
    }
    return result; //return total path
}

vector<FlightEdge> DjikstrasModAlgo::getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool> &reached) {
    short cur = dest;
    vector<FlightEdge> path;
    while (cur != src) { //while we haven't reached our source
        reached[cur] = true; //we have reached current, in case we go back
        short last = p[cur]; //from previous node
        FlightEdge edge;
        edge.price = d[cur] - d[last]; //get the weight of this edge
        edge.destWAC = cur; //our destination
        edge.originWAC = last;
        edge.airlineCode = g->getAirlineFromData(edge.originWAC,edge.destWAC, edge.price);
        path.push_back(edge);
        cur = last; //go back to the origin of this edge and repeat algorithm until reach our source (src)
    }
    return path;
}

short DjikstrasModAlgo::minDistance(FlightGraph* g, map<short, bool> reached) {

    // Initialize min value
    double min = DBL_MAX;
    short closest;

    for (auto itr = reached.begin(); itr != reached.end(); itr++) //for all entries in reached
        if (!itr->second && d[itr->first] <= min) // if not reached and its distance is less than curr smallest
            min = d[itr->first], closest = itr->first; //set that is the smallest node

    return closest; //return the smallest node
}
