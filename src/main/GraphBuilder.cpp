#include "../libs/GraphBuilder.h"
#include "../libs/RouteSearch.h"
#include <sstream>
#include <fstream>
#include <vector>


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

        g->addBidirectionalEdge(location1, location2, car, foot);

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
        bool p = parking=="1";

        g->addVertex(idL, location, code, p);

    }
    inL.close();
}

void deselect(Graph<std::string> * g) {
    for (auto v : g->getVertexSet()) {
        v->setSelected(false);
        for (auto e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}
