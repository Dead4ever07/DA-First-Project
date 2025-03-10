//
// Created by luis-santos on 2/27/25.
//

#include "../libs/GraphBuilder.h"
#include <sstream>
#include <fstream>


void graphDistance(Graph<std::string>* g, std::string distances){
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

        //std::cout << "l1: " << location1 << "l2: " << location2 << "d: " << driving << "w: " << walking << "c: " << car << "f: " << foot<< std::endl;

        g->addEdge(location1, location2, car, foot); //perguntar

    }
    inD.close();
}

void graphLocation(Graph<std::string>* g, std::string locations){
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

        int idL = std::stoi(id);
        bool p = 0;
        if (parking == "1") {
            p=1;
        }

        //std::cout << "l: " << location << "id: " << id << "idl: " << idL << "c: " << code  << "pk: " << parking << "p: " << p << std::endl;

        g->addVertex(location, idL, code, p); //perguntar

    }
    inL.close();
}