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

void readInputFromFile(Graph<std::string>* g, std::string fileName, std::string& output) {
    std::ifstream in("../resources/" + fileName);
    if (!in) {
        std::cerr << "Error opening input file"<< std::endl;
        return;
    }
    std::string s(std::istreambuf_iterator<char>(in), {});
    readInputFromString(g, s, output);
}

void readInputFromString(Graph<std::string>* g , std::string input, std::string& output) {
    std::istringstream in(input);
    std::string line, mode, source, destination, nodesLine;
    int iSource, iDestination, maxWalkTime, includeNode = -1;
    std::vector<int> avoidNodes = {};
    std::vector<std::pair<int,int>> avoidSegments = {};
    while (getline(in, line)) {
        std::istringstream iss(line);
        std::string m;
        getline(iss, m, ':');
        if (m == "Mode") {
            getline(iss, mode, '\r');
        }
        else if (m == "Source") {
            getline(iss, source);
            try{
            iSource = stoi(source);
            }
            catch (std::exception &err) {
                output = "Invalid Source inserted:(" + source + ")!";
                return;
            }
        }
        else if (m == "Destination") {
            getline(iss, destination);
            try {
                iDestination = stoi(destination);
            }
            catch (std::exception &err) {
                output = "Invalid Destination inserted:(" + destination + ")!";
                return;
            }
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
        }
        else if (m == "IncludeNode") {
            getline(iss, nodesLine);
            std::istringstream issNodesLine(nodesLine);
            issNodesLine >> includeNode;
        }
        else if (m == "MaxWalkTime") {
            getline(iss, nodesLine);
            std::istringstream issNodesLine(nodesLine);
            issNodesLine >> maxWalkTime;
        }
    }
    output = checkInput(g, iSource, iDestination, avoidNodes, avoidSegments, includeNode, mode,maxWalkTime);
}

std::string checkInput(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle, std::string mode, int maxWalkTime) {

    Vertex<std::string>* originVertex = g->idFindVertex(origin);
    if (originVertex == nullptr) {
        return "Invalid Source inserted:(" + std::to_string(origin) + ")!";
    }

    Vertex<std::string>* destVertex = g->idFindVertex(dest);
    if (destVertex == nullptr) {
        return "Invalid Destination inserted:(" + std::to_string(dest) + ")!";
    }

    std::string result = "Source:" + std::to_string(origin) + "\n" + "Destination:" + std::to_string(dest)+'\n';


        if (middle == -1 && vertex.empty() && edges.empty() && mode == "driving") {
            result.append(driveRoute(g,originVertex, destVertex));
            return result;
        }

    if (!(middle == -1 || g->idFindVertex(middle) != nullptr)) {
        return "Invalid IncludeNode inserted:(" + std::to_string(middle) + ")!";
    }

    for (const int id : vertex) {
        Vertex<std::string> *vertex = g->idFindVertex(id);
        if (vertex == nullptr) {
            return "Invalid AvoidNode inserted:(" + std::to_string(id) + ")!";
        }
        vertex->setSelected(true);
    }

    for (std::pair<int,int> p : edges) {
        Vertex<std::string> *originVertex = g->idFindVertex(p.first);
        if (originVertex == nullptr) {
            return "Invalid AvoidSegment inserted:(" + std::to_string(p.first) + "," + std::to_string(p.second) + ")!";
        }
        bool error = true;
        for (auto e : originVertex->getAdj()) {
            if (e->getDest()->getId() == p.second) {
                e->setSelected(true);
                error = false;
            }
        }
        if (error) {
            return "Invalid AvoidSegment inserted:(" + std::to_string(p.first) + "," + std::to_string(p.second) + ")!";
        }
    }
    if(mode == "driving") {
        result.append(driveRestrictedRoute(g,originVertex,destVertex,middle));
    }
    else if(mode == "driving-walking") {
        result.append(driveWalkingRoute(g,originVertex,destVertex,maxWalkTime));
    }
    else {
        return "Invalid Mode inserted:(" + mode + ")!";
    }
    return result;
}

void deselect(Graph<std::string> * g) {
    for (auto v : g->getVertexSet()) {
        v->setSelected(true);
        for (auto e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}
