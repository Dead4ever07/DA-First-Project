//
// Created by luis-santos on 2/27/25.
//

#include "../libs/GraphBuilder.h"
#include "libs/Graph.h"
#include <sstream>
#include <fstream>


void graphDistance(Graph<int>* g, std::string distances){
    std::ifstream inD(distances);
    if (!inD) {
        std::cerr << "Error opening file " << distances << std::endl;
        return;
    }
    std::string line;
    getline(inD, line); //ignorar primeira linha

    while (getline(inD, line)) {
        std::istringstream iss(line);
        std::string location1, location2, driving, walking, paragraph, v;

        getline(iss, location1, ',');
        getline(iss, location2, ',');
        getline(iss, driving, ',');
        getline(iss, walking, ',');

        int car = -1;
        if (driving != "X") {
            car = std::stoi(driving);
        }
        int foot = std::stoi(walking);

        std::cout << "l1: " << location1 << "l2: " << location2 << "d: " << driving << "w: " << walking << "c: " << car << "f: " << foot<< std::endl;

        //g->addEdge(location1, location2, car, foot);

    }
    inD.close();
}

void graphLocation(Graph<int>* g, std::string locations){
    std::ifstream inL(locations);
    if (!inL) {
        std::cerr << "Error opening file " << locations << std::endl;
        return;
    }
    std::string line;
    getline(inL, line);

    while (getline(inL, line)) {
        std::istringstream iss(line);
        std::string location, id, code, parking;

        getline(iss, location, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, parking, ',');

        bool p = 0;
        if (parking == "1") {
            p=1;
        }

        std::cout << "l: " << location << "id: " << id << "c: " << code  << "pk: " << parking << "p: " << p << std::endl;

        //g->addVertex(id, location, code, p);

    }
    inL.close();
}

void readInput() {
    std::ifstream in("../resources/input.txt");
    if (!in) {
        std::cerr << "Error opening input file"<< std::endl;
        return;
    }
    std::string line, mode, source, destination;
    while (getline(in, line)) {
        std::istringstream iss(line);
        std::string m;
        getline(iss, m, ':');
        std::cout << m;
        if (m == "Mode") {
            getline(iss, mode);
            std::cout << mode << std::endl;
        }
        else if (m == "Source") {
            getline(iss, source);
            std::cout << source << std::endl;
        }
        else if (m == "Destination") {
            getline(iss, destination);
            std::cout << destination << std::endl;
        }
    }
}
