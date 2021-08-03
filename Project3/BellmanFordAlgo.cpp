#include "BellmanFordAlgo.h"

void BellmanFordAlgo::bellmanFord(FlightGraph *g, short source) {

    int V = g->V;
    int E = g->E;

    for (auto itr = g->graph.begin(); itr != g->graph.end(); itr++) { //for all vertices
        d[itr->first] = DBL_MAX; //assigning our d and b
        p[itr->first] = 0;
    }
    d[source] = 0; //initialize our source
	//Basically will run all potential combinations as opposed to the heuristically driven Dijkstra, shown by running the whole double for loop V-1 times
    for (int i = 1; i <= V-1; i++) { // run for V-1 times
        for (auto itr = g->graph.begin(); itr != g->graph.end(); itr++) { //for all vertices
            for (int j = 0; j < itr->second.size(); j++) { //for all edges at vertice
                short u = itr->second.at(j).originWAC; //assign temp origin
                short v = itr->second.at(j).destWAC; //assign temp destination
                double weight = itr->second.at(j).price; //assign temp weight
                if (d[u] != DBL_MAX && d[u] + weight < d[v]) { //relaxation
                    d[v]= d[u] + weight;
                    p[v] = u;
                }
            }
        }
    }

}

vector<FlightEdge> BellmanFordAlgo::calculateRoute(FlightGraph *g, short source, vector<short> dest) {
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
        bellmanFord(g, src); //finds paths to all nodes
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
    bellmanFord(g, finalDest);
    vector<FlightEdge> returnPath = getCurrentPath(g, finalDest, source, hold); //return back to original source
    for (int i = returnPath.size()-1; i >= 0; i--) {
        result.push_back(returnPath.at(i));
    }
    return result; //return total path

}

vector<FlightEdge> BellmanFordAlgo::getCurrentPath(FlightGraph *g, short src, short dest, map<short, bool>& reached) {
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
