//
// Created by luis-santos on 2/27/25.
//

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

Graph<std::string> *createGraph() {
    Graph<std::string>* g = new Graph<std::string>();
    graphLocation(g, "../resources/SmallLocations.csv");
    graphDistance(g, "../resources/SmallDistances.csv");
    return g;
}


void readInput(std::string input) {
    std::ifstream in("../resources/" + input);
    if (!in) {
        std::cerr << "Error opening input file"<< std::endl;
        return;
    }
    std::string line, mode, source, destination, nodesLine;
    int iSource, iDestination;
    std::vector<int> avoidNodes = {};
    std::vector<std::pair<int,int>> avoidSegments = {};
    int includeNode = -1;
    while (getline(in, line)) {
        std::istringstream iss(line);
        std::string m;
        getline(iss, m, ':');
        //std::cout << m;
        if (m == "Mode") {
            getline(iss, mode);
            //std::cout << mode << std::endl;
        }
        else if (m == "Source") {
            getline(iss, source);
            iSource = stoi(source);
            //std::cout << source << std::endl;
        }
        else if (m == "Destination") {
            getline(iss, destination);
            iDestination = stoi(destination);
            //std::cout << destination << std::endl;
        }
        else if (m == "AvoidNodes") {
            getline(iss, nodesLine);
            std::istringstream issNodesLine(nodesLine);
            int node;
            while (issNodesLine >> node) {
                char comma;
                issNodesLine >> comma;
                avoidNodes.push_back(node);
            }
            //std::cout << destination << std::endl;
        }
        else if (m == "AvoidSegments") {
            getline(iss, nodesLine);
            std::istringstream issNodesLine(nodesLine);
            char comma, pLeft, pRight;
            std::pair<int, int> segment;
            while (issNodesLine >> pLeft) {
                issNodesLine >> segment.first >> comma >> segment.second >> pRight >> comma ;
                avoidSegments.push_back(segment);
            }
            //std::cout << destination << std::endl;
        }
        else if (m == "IncludeNode") {
            getline(iss, nodesLine);
            std::istringstream issNodesLine(nodesLine);
            issNodesLine >> includeNode;
            //std::cout << includeNode << std::endl;
        }
    }
    Graph<std::string> *g = createGraph();
    if (mode == "driving") {
        if (includeNode != -1 || !avoidNodes.empty() || !avoidSegments.empty() ) {
            //std::cout << "sitio certo\n";
            driveRestrictedRoute(g,iSource,iDestination,avoidNodes, avoidSegments, includeNode);
        }
        else {
            driveRoute(g,iSource, iDestination);
        }
    }
    else if(mode == "driving-walking") {
        //wip
        return;
    }

}
