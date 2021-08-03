//
//  main.cpp
//  Project3
//
//  Created by Chase Wrenn on 8/2/21.
//


// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <fstream>
#include<string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "FileManager.h"
#include "FlightEdge.h"
#include "FlightGraph.h"
#include "BellmanFordAlgo.h"
#include "DjikstrasModAlgo.h"
using namespace std;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void readData(map <string, string>& airLineData, map <string, int>& locationData)
{
    //read airline data
    string filePathAirlines = "airlines.txt";
    string lineFromFile;
    ifstream myFile(filePathAirlines);
    while (getline(myFile, lineFromFile))
    {
        istringstream stream(lineFromFile);
        string ID;
        string name;
        getline(stream, ID, ',');
        getline(stream, name, ',');
        if (ID != "")
        {
            airLineData[name] = ID;
            //cout << airLineData[name];
        }
    }
    myFile.close();

    //read locaiton data
    string filePathLocations = "locations.txt";
    ifstream myFile2(filePathLocations);
    while (getline(myFile2, lineFromFile))
    {
        istringstream stream(lineFromFile);
        string number;
        string name;
        int numFinal;
        getline(stream, number, ' ');
        getline(stream, name);
        if (number != "")
        {
            numFinal = stoi(number);
            locationData[name] = numFinal;
        }
    }
    myFile2.close();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//drawing functions

void loadWidgets(tgui::GuiBase& gui, vector <tgui::Button::Ptr>& startingPointButtons, vector <tgui::Button::Ptr>& destinationButtons, vector <tgui::Button::Ptr>& airlineButtons,
    vector <tgui::Button::Ptr>& quarterButtons, tgui::Button::Ptr& computeButton, map<string, string>& airlineData, map <string, int>& locationData, string* startPointPointer, set<string>* destinationsPointer,
    set<string>* airLinesPointer, string* quarterPointer)
{
    tgui::Theme::setDefault("BabyBlue.txt");
    //tgui::Theme blackTheme{ "C:/APIs/TGUI-0.9/themes/Black.txt" };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Starting point scrollbar
    //create label
    auto startLocationLabel = tgui::Label::create();
    startLocationLabel->setText("Starting Point");
    startLocationLabel->setPosition(50, 25);
    startLocationLabel->setTextSize(18);
    gui.add(startLocationLabel);

    //create scrollbar
    auto startLocationPanel = tgui::ScrollablePanel::create();
    startLocationPanel->setPosition(50, 50);
    startLocationPanel->setSize(250, 250);
    gui.add(startLocationPanel);


    // Create locations
    auto iter1 = locationData.begin();
    int i1 = 0;
    for (iter1; iter1 != locationData.end(); iter1++)
    {
        tgui::Button::Ptr button = tgui::Button::create();
        button->setText(iter1->first);
        button->setSize(250, 25);
        button->setPosition(0, i1 * 25);
        startingPointButtons.push_back(button);
        startLocationPanel->add(button);
        i1++;
    }
    startLocationPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Destinations scrollbar

    //create label
    auto destinationLabel = tgui::Label::create();
    destinationLabel->setText("Destinations");
    destinationLabel->setPosition(350, 25);
    destinationLabel->setTextSize(18);
    gui.add(destinationLabel);

    //create scrollbar
    auto destinationPanel = tgui::ScrollablePanel::create();
    destinationPanel->setPosition(350, 50);
    destinationPanel->setSize(250, 250);
    gui.add(destinationPanel);


    // Create locations
    auto iter2 = locationData.begin();
    int i2 = 0;
    for (iter2; iter2 != locationData.end(); iter2++)
    {
        tgui::Button::Ptr button = tgui::Button::create();
        button->setText(iter2->first);
        button->setSize(250, 25);
        button->setPosition(0, i2 * 25);
        destinationButtons.push_back(button);
        destinationPanel->add(button);
        i2++;
    }
    destinationPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Airlines scrollbar

    //create label
    auto airinesLabel = tgui::Label::create();
    airinesLabel->setText("Airlines");
    airinesLabel->setPosition(50, 325);
    airinesLabel->setTextSize(18);
    gui.add(airinesLabel);

    //create scrollbar
    auto airinesPanel = tgui::ScrollablePanel::create();
    airinesPanel->setPosition(50, 350);
    airinesPanel->setSize(250, 250);
    gui.add(airinesPanel);


    // Create airlines
    auto iter3 = airlineData.begin();
    int i3 = 0;
    for (iter3; iter3 != airlineData.end(); iter3++)
    {
        tgui::Button::Ptr button = tgui::Button::create();
        button->setText(iter3->first);
        //cout << iter3->first << endl;
        button->setSize(250, 25);
        button->setPosition(0, i3 * 25);
        airlineButtons.push_back(button);
        airinesPanel->add(button);
        i3++;
    }
    airinesPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Quarters scrollbar

    //create label
    auto quartersLabel = tgui::Label::create();
    quartersLabel->setText("Quarter");
    quartersLabel->setPosition(350, 325);
    quartersLabel->setTextSize(18);
    gui.add(quartersLabel);

    //create scrollbar
    auto quartersPanel = tgui::ScrollablePanel::create();
    quartersPanel->setPosition(350, 350);
    quartersPanel->setSize(250, 250);
    gui.add(quartersPanel);


    // Create Quarters
    for (unsigned int i = 1; i < 5; ++i)
    {
        tgui::Button::Ptr button = tgui::Button::create();
        button->setText(to_string(i));
        button->setSize(250, 25);
        button->setPosition(0, (i-1) * 25);
        quarterButtons.push_back(button);
        quartersPanel->add(button);
    }
    quartersPanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    //create calculate button
    tgui::Button::Ptr button = tgui::Button::create();
    button->setSize(500, 50);
    button->setPosition(650, 275);
    button->setText("Compute");
    computeButton = button;
    gui.add(button);
}

void createInput(tgui::GuiBase& gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer)
{
    //Create input window

    //create label
    auto inputLabel = tgui::Label::create();
    inputLabel->setText("Input");
    inputLabel->setPosition(650, 25);
    inputLabel->setTextSize(18);
    gui.add(inputLabel);

    auto listBox1 = tgui::ListBox::create();
    listBox1->setSize(500, 200);
    listBox1->setPosition(650, 50);
    listBox1->setItemHeight(25);
    listBox1->addItem("Starting Point: " + *startPointPointer);
    listBox1->addItem("Quarter: " + *quarterPointer);

    if (airLinesPointer->begin() == airLinesPointer->end())
    {
        listBox1->addItem("Airlines: ");
    }
    else
    {
        listBox1->addItem("Airlines:  " + *airLinesPointer->begin());
        auto iter = airLinesPointer->begin();
        iter++;
        for (iter; iter != airLinesPointer->end(); iter++)
        {
            listBox1->addItem("               " + *iter);
        }
    }

    if (destinationsPointer->begin() == destinationsPointer->end())
    {
        listBox1->addItem("Destinations: ");
    }
    else
    {
        listBox1->addItem("Destinations: " + *destinationsPointer->begin());
        auto iter = destinationsPointer->begin();
        iter++;
        for (iter; iter != destinationsPointer->end(); iter++)
        {
            listBox1->addItem("                      " + *iter);
        }
    }
    
    gui.add(listBox1);
}

void createOutput(tgui::GuiBase& gui, string* outputPointer)
{
    //Create input window

    //create label
    auto outputLabel = tgui::Label::create();
    outputLabel->setText("Output");
    outputLabel->setPosition(650, 325);
    outputLabel->setTextSize(18);
    gui.add(outputLabel);

    auto listBox2 = tgui::ListBox::create();
    listBox2->setSize(500, 250);
    listBox2->setPosition(650, 350);
    listBox2->setItemHeight(100);
    listBox2->addItem(*outputPointer);

    gui.add(listBox2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Actual computations




string compute(string* startPointPointer, set<string>* destinationsPointer, set<string>* airlinePointer, string* quarterPointer)
{
    FileManager f;
    FlightGraph flightGraph;
    short q = stoi(*quarterPointer);
    string src = *startPointPointer;
    vector<short> dest;
    map<string, bool> airlines;
    for (auto it = airlinePointer->begin(); it != airlinePointer->end(); ++it)
    {
        airlines[*it] = true;
    }

    for (auto it = destinationsPointer->begin(); it != destinationsPointer->end(); ++it)
    {
        dest.push_back((flightGraph.getACfromLoc(*it)));
    }
    f.buildGraph("Cleaned_2018_Flights.csv", q, airlines, flightGraph);
    BellmanFordAlgo bellmanFordAlgo;
    DjikstrasModAlgo djikstra;
    vector<FlightEdge> route, route2;

    auto start = std::chrono::high_resolution_clock::now();
    route = djikstra.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    auto start2 = std::chrono::high_resolution_clock::now();
    route2 = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    string output = "\n\n\n\nBellman Ford Algorithm Time: " + to_string(duration2.count());
    output = output + " microseconds\nDijkstra Algorithm Time: ";
    output = output + to_string(duration.count()) + " microseconds\n";
    output += flightGraph.routeText(route2);
    return output;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//button pressed functions


void startingPointPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, tgui::String buttonText)
{
    std::string strUtf8(buttonText);
    *startPointPointer = strUtf8;
    createInput(*gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
    //cout << *startPointPointer;
}

void destinationPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, tgui::String buttonText)
{
    std::string strUtf8(buttonText);
    set <string> tmp = *destinationsPointer;
    if (destinationsPointer->find(strUtf8) == destinationsPointer->end())
    {
        destinationsPointer->insert(strUtf8);
    }
    else
    {
        destinationsPointer->erase(strUtf8);
    }
    createInput(*gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
}


void airlinePressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, tgui::String buttonText)
{
    std::string strUtf8(buttonText);
    set <string> tmp = *airLinesPointer;
    if (airLinesPointer->find(strUtf8) == airLinesPointer->end())
    {
        airLinesPointer->insert(strUtf8);
    }
    else
    {
        airLinesPointer->erase(strUtf8);
    }
    createInput(*gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
    //cout << *airLinePointer;
}

void quarterPressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, tgui::String buttonText)
{
    std::string strUtf8(buttonText);
    *quarterPointer = strUtf8;
    createInput(*gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
    //cout << *quarterPointer;
}

void computePressed(tgui::GuiBase* gui, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, string* outputPointer, map <string, string>* airlineDataFinal)
{
    //int startPointFinal = (*locationData)[*startPointPointer];
    set <string> airlinesFinal;
    auto iter = airLinesPointer->begin();
    for (iter; iter != airLinesPointer->end(); iter++)
    {
        string airlineCode = (*airlineDataFinal)[*iter];
        airlinesFinal.insert(airlineCode);
    }
    set<string>* airlinesFinalPointer = &airlinesFinal;
    //cout << airlineFinal;

    string output = compute(startPointPointer, destinationsPointer, airlinesFinalPointer, quarterPointer);
    *outputPointer = output;
    createOutput(*gui, outputPointer); //prints output. Do this after storing the output in *outputPointer, don't change this method

    //clear all data
    //*startPointPointer = "";
    //destinationsPointer->clear();
    //*airLinePointer = "";
    //*quarterPointer = "";
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


bool runCode(tgui::GuiBase& gui, vector <tgui::Button::Ptr>& startingPointButtons, vector <tgui::Button::Ptr>& destinationButtons, vector <tgui::Button::Ptr>& airlineButtons, vector <tgui::Button::Ptr>& quarterButtons,
    tgui::Button::Ptr& computeButton, map<string, string>& airlineData, map <string, int>& locationData, string* startPointPointer, set<string>* destinationsPointer, set<string>* airLinesPointer, string* quarterPointer, string* outputPointer)
{
    map <string, string>* airlineDataFinal = &airlineData;
    //cout << (*airlineDataFinal)["American Airlines Inc."];
    try
    {
        loadWidgets(gui, startingPointButtons, destinationButtons, airlineButtons, quarterButtons, computeButton, airlineData, locationData, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        createInput(gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        createOutput(gui, outputPointer);
        for (int i = 0; i < startingPointButtons.size(); i++)
        {
            startingPointButtons[i]->onPress(&startingPointPressed, &gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        }
        for (int i = 0; i < destinationButtons.size(); i++)
        {
            destinationButtons[i]->onPress(&destinationPressed, &gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        }
        for (int i = 0; i < airlineButtons.size(); i++)
        {
            airlineButtons[i]->onPress(&airlinePressed, &gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        }
        for (int i = 0; i < quarterButtons.size(); i++)
        {
            quarterButtons[i]->onPress(&quarterPressed, &gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer);
        }
        computeButton->onPress(&computePressed, &gui, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer, outputPointer, airlineDataFinal);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

int main()
{
    vector <tgui::Button::Ptr> startingPointButtons;
    vector <tgui::Button::Ptr> destinationButtons;
    vector <tgui::Button::Ptr> airlineButtons;
    vector <tgui::Button::Ptr> quarterButtons;
    tgui::Button::Ptr computeButton;

    map <string, string> airlineData;
    map <string, int> locationData;

    string startPoint;
    string* startPointPointer = &startPoint;

    string airLine;
    string* airLinePointer = &airLine;
    set<string> airLines;
    set<string>* airLinesPointer = &airLines;

    set<string> destinations;
    set<string>* destinationsPointer = &destinations;

    string quarter;
    string* quarterPointer = &quarter;
    int quarterFinal;

    string output = "";
    string* outputPointer = &output;

    bool redrawInputOutput;
    bool* redrawInputOutputPointer = &redrawInputOutput;

    sf::RenderWindow window(sf::VideoMode(1200, 650), "Flight Optimization Project 3B");

    //read data
    readData(airlineData, locationData);

    tgui::Gui gui(window);

    if (!runCode(gui, startingPointButtons, destinationButtons, airlineButtons, quarterButtons, computeButton, airlineData, locationData, startPointPointer, destinationsPointer, airLinesPointer, quarterPointer, outputPointer))
        return EXIT_FAILURE;

    gui.mainLoop();

    return EXIT_SUCCESS;
}


/*
#include <iostream>
#include <sstream>
#include "Data/FileManager.h"
#include "Function/BellmanFordAlgo.h"
#include "Function/DjikstrasModAlgo.h"
#include <chrono>

using namespace std;

int main() {
    FileManager f;
    FlightGraph flightGraph;
    bool incomplete = true;
    short q;
    string src;
    vector<short> dest;
    map<string, bool> airlines;
    cout << "Welcome to Travel Optimization BETA!" << endl;
    while (incomplete) {
        cout << "Please enter the quarter of the year "
            "you would like to take your trip:" << endl;
        cin >> q;
        if (q < 0 || q > 4) {
            cout << "Error! Quarter must be between 1 and 4!" << endl;
            q = 0;
        }
        else
            incomplete = false;
    }
    cout << "Please enter the source of the trip:" << endl;
    cin >> src;
    cout << "Enter Airline codes of airlines you would like to use,"
        " separated by a comma. (Ex: WN,DL):" << endl;
    cout << "WN Southwest Airlines Co.\n"
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
    string str;
    cin >> str;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        airlines.insert(make_pair(substr, true));
    }
    cout << "Enter Area Codes of locations you would like to go to, "
        "separated by a comma. (Ex: 2,13):" << endl;
    cout << "1 Alaska\n"
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
    string str2;
    cin >> str2;
    stringstream ss2(str2);
    while (ss2.good()) {
        string substr;
        getline(ss2, substr, ',');
        dest.push_back(stoi(substr));
    }
    //f.buildGraph("smallSampleData.csv", q, airlines, flightGraph);
    f.buildGraph("Cleaned_2018_Flights.csv", q, airlines, flightGraph);
    BellmanFordAlgo bellmanFordAlgo;
    DjikstrasModAlgo djikstra;
    vector<FlightEdge> route, route2;
    route = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);

    auto start2 = std::chrono::high_resolution_clock::now();
    route2 = bellmanFordAlgo.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    auto start = std::chrono::high_resolution_clock::now();
    route = djikstra.calculateRoute(&flightGraph, flightGraph.WAC[src], dest);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Bellman Ford Output:" << endl;
    string out = flightGraph.routeText(route2);
    cout << out << endl;
    cout << "Bellman Ford Algorithm Time: " << duration2.count() << " microseconds" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Djikstra Output:" << endl;
    string out2 = flightGraph.routeText(route);
    cout << out2 << endl;
    cout << "Dijkstra Algorithm Time: " << duration.count() << " microseconds" << endl;
    //for (int i = 0; i < route.size(); i++) {
    //     FlightEdge e = route.at(i);
    //     cout << flightGraph.getLocFromAC(e.originWAC) << "--->" <<
    //         flightGraph.getLocFromAC(e.destWAC) << "; Price: $" << e.price << "; Airline: " <<
    //         flightGraph.getAirlineFromCode(e.airlineCode) << endl;
    // }

     
}
*/
//Test Flight Data Cleaned_2018_Flights
