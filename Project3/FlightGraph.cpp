#include <vector>
#include <sstream>
#include "FlightGraph.h"
#include "iomanip"

FlightGraph::FlightGraph() {

    string string1 = "1 Alaska\n" //Each provides WAC and location pair
                     "2 Hawaii\n"
                     "3 Puerto Rico\n"
                     "4 U.S. Virgin Islands\n"
                     "5 U.S. Pacific Trust Territories and Possessions\n"
                     "11 Connecticut\n"
                     "12 Maine\n"
                     "13 Massachusetts\n"
                     "14 New Hampshire\n"
                     "15 Rhode Island\n"
                     "16 Vermont\n"
                     "21 New Jersey\n"
                     "22 New York\n"
                     "23 Pennsylvania\n"
                     "31 Delaware\n"
                     "32 District of Columbia\n"
                     "33 Florida\n"
                     "34 Georgia\n"
                     "35 Maryland\n"
                     "36 North Carolina\n"
                     "37 South Carolina\n"
                     "38 Virginia\n"
                     "39 West Virginia\n"
                     "41 Illinois\n"
                     "42 Indiana\n"
                     "43 Michigan\n"
                     "44 Ohio\n"
                     "45 Wisconsin\n"
                     "51 Alabama\n"
                     "52 Kentucky\n"
                     "53 Mississippi\n"
                     "54 Tennessee\n"
                     "61 Iowa\n"
                     "62 Kansas\n"
                     "63 Minnesota\n"
                     "64 Missouri\n"
                     "65 Nebraska\n"
                     "66 North Dakota\n"
                     "67 South Dakota\n"
                     "71 Arkansas\n"
                     "72 Louisiana\n"
                     "73 Oklahoma\n"
                     "74 Texas\n"
                     "81 Arizona\n"
                     "82 Colorado\n"
                     "83 Idaho\n"
                     "84 Montana\n"
                     "85 Nevada\n"
                     "86 New Mexico\n"
                     "87 Utah\n"
                     "88 Wyoming\n"
                     "91 California\n"
                     "92 Oregon\n"
                     "93 Washington";

    std::istringstream f(string1);
    std::string line;
    while (std::getline(f, line)) {
        int index = line.find(' ');
        short AC = stoi(line.substr(0,index));
        string loc = line.substr(index+1, line.size());
        WAC.insert(make_pair(loc, AC)); //make the WAC (world area code) and location a pair and add to map
    }

    string string2 = "WN Southwest Airlines Co.\n" //each line has pair of airline code and airline
                     "DL Delta Air Lines Inc.\n"
                     "AA American Airlines Inc.\n"
                     "UA United Air Lines Inc.\n"
                     "B6 JetBlue Airways\n"
                     "AS Alaska Airlines Inc.\n"
                     "NK Spirit Air Lines\n"
                     "G4 Allegiant Air\n"
                     "F9 Frontier Airlines Inc.\n"
                     "HA Hawaiian Airlines Inc.\n"
                     "SY Sun Country Airlines d/b/a MN Airlines\n"
                     "VX Virgin America";

    std::istringstream g(string2);
    std::string line2;
    while (std::getline(g, line2)) {
        int index = line2.find(' ');
        string code = line2.substr(0,index);
        string name = line2.substr(index+1, line2.size());
        airlines.insert(make_pair(code, name)); //make pair of airline code and airline, add to map
    }

    V = 0;
    E = 0;
}


void FlightGraph::insertFlightEdge(FlightEdge &e)
{
    if (graph.find(e.originWAC) == graph.end()) {//if origin WAC not in map
        graph[e.originWAC] = {}; //add to map
        V++; //++ number of vertices
    }
    if (graph.find(e.destWAC) == graph.end()) {//if destination WAC not in map
        graph[e.destWAC] = {}; //add to map
        V++;//++ number of vertices

    }
    graph[e.originWAC].push_back(e); //add the edge to the adjacency list "graph"
    E++; //++ number of edges

}

bool FlightGraph::isFlight(FlightEdge &e) { //unused
    //Search in flightgraph if there exists in 
    // flight x = graph[e.originWAC]
    return false;
}

bool FlightGraph::isFlight(short src, short dest) //check to see if flight exists
{
    for (int i = 0; i < graph[src].size(); i++)
    {
        if (graph[src].at(i).originWAC == src && graph[src].at(i).destWAC == dest) //if there is a flight with same origin/destination
            return true;
    }
    return false;
}

double FlightGraph::getPrice(string src, string dest) { //unused
    return 0.0;
}

vector<FlightEdge> FlightGraph::getFlightsFromLoc(short src) {
    vector<FlightEdge> flights;
    return flights;
}

void FlightGraph::printGraph() { //this was used in debugging to help show the graph, we later just created a string for the GUI
    cout << "List of All Flights in Graph:" << endl;
    for (auto it = graph.begin(); it != graph.end(); ++it)
    {
        for (int i = 0; i < it->second.size(); i++)
            cout << it->second.at(i).originWAC << "->" << it->second.at(i).destWAC << endl; //print out the flight data
    }
}

string FlightGraph::getAirlineFromData(short src, short dest, double price) {
    string airline = "";
    bool found = false;
    for (int i = 0; i < graph[src].size() && !found; i++) { //for all edges at vertex
        FlightEdge e = graph[src].at(i); //get one flightedge
        if (e.originWAC == src && e.destWAC == dest && e.price == price) { //check if flightedge is the one we want
            airline = e.airlineCode; //get our airline
            found = true;
        }
    }
    return airline;
}

double FlightGraph::getWeight(short src, short dest)
{
    double lowestWeight = std::numeric_limits<double>::max();
    for (int i = 0; i < graph[src].size(); i++) //for all edges at src
    {
        if (graph[src].at(i).destWAC = dest) //if correct dest
        {
            if (graph[src].at(i).price < lowestWeight)
                lowestWeight = graph[src].at(i).price;
        }
    }
    return lowestWeight;
}

string FlightGraph::getLocFromAC(short AC) {
    string res = "";
    for (auto itr = WAC.begin(); itr != WAC.end() && res == ""; itr++) //for all vertices
    {
        if (itr->second == AC) //if we find the WAC we want
        {
            res = itr->first; //return the location
        }
    }
    return res;
}

short FlightGraph::getACfromLoc(string loc) {
    return WAC.find(loc)->second;
}

string FlightGraph::getAirlineFromCode(string code) {
    return airlines[code];
}

string FlightGraph::routeText(vector<FlightEdge> route) {
    string res;
    for (int i = 0; i < route.size(); i++) { //for all edges in our route
        FlightEdge e = route.at(i); //assign flight edge
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << e.price; //for prices -> to two decimal places
         res += getLocFromAC(e.originWAC) + "--->" +
             getLocFromAC(e.destWAC) + "; Price: $" + stream.str() + "; Airline: " +
             getAirlineFromCode(e.airlineCode) + "\n"; //create string
    }
    return res;
}
