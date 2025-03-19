#include "../libs/GraphBuilder.h"
#include "../libs/RouteSearch.h"
#include <sstream>
#include <fstream>
#include <vector>


/**
 * Reads distance data from a file and adds edges to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param distances Path to the file containing distances between locations.
 * @note Time Complexity: O(E), where E is the number of edges in the file
 */
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

/**
 * Reads location data from a file and adds vertices to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param locations Path to the file containing location data.
 * @note Time Complexity: O(V), where V is the number of vertices in the file.
 */
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

/**
 * Creates and initializes a graph with locations and distances from files.
 *
 * @return Pointer to the created Graph object.
 *
 * @note Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges
 */
Graph<std::string> *createGraph() {
    Graph<std::string>* g = new Graph<std::string>();
    graphLocation(g, "../resources/SmallLocations.csv");
    graphDistance(g, "../resources/SmallDistances.csv");
    return g;
}

/**
 * Reads and processes input commands to determine a route based on a given mode.
 *
 * @param input Filename of the input file containing route parameters.
 *
 * @note Time Complexity: O(L + M + N + A + (V + E)log V), where:
 *   - L is the number of lines in the input file,
 *   - V is the number of vertices,
 *   - E is the number of edges,
 *   - A is the number of avoid nodes/segments.
 *   - (V + E)log V is the time complexity of a Dijkstra search,
 */
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
    int iSource, iDestination, maxWalkTime;
    std::vector<int> avoidNodes = {};
    std::vector<std::pair<int,int>> avoidSegments = {};
    int includeNode = -1;
    while (getline(in, line)) {
        std::istringstream iss(line);
        std::string m;
        getline(iss, m, ':');
        if (m == "Mode") {
            getline(iss, mode, '\r');
        }
        else if (m == "Source") {
            getline(iss, source);
            iSource = stoi(source);
        }
        else if (m == "Destination") {
            getline(iss, destination);
            iDestination = stoi(destination);
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
            //std::cout << maxWalkTime << std::endl;
        }
    }
     std::cout << checkInput(g, iSource, iDestination, avoidNodes, avoidSegments, includeNode, mode);
}

std::string checkInput(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle, std::string mode) {

    Vertex<std::string>* originVertex = g->idFindVertex(origin);
    if (originVertex == nullptr) {
        return "Invalid Source inserted:(" +std::to_string(origin) + ")!";
    }

    Vertex<std::string>* destVertex = g->idFindVertex(dest);
    if (destVertex == nullptr) {
        return "Invalid Destination inserted:(" +std::to_string(dest) + ")!";
    }

    std::string result = "Source:" + std::to_string(origin) + "\n" + "Dest:" + std::to_string(dest)+'\n';

    if (mode == "driving") {
        if (middle == -1 && vertex.empty() && edges.empty() ) {
            //std::cout << "sitio certo\n";
            result.append(driveRoute(g,originVertex, destVertex));
            return result;
        }

        if (middle == -1 || g->idFindVertex(middle) == nullptr) {
            return "Invalid IncludeNode inserted:(" +std::to_string(middle) + ")!";
        }

        for (const int id : vertex) {
            Vertex<std::string> *vertex = g->idFindVertex(id);
            if (vertex == nullptr) {
                return "Invalid AvoidNode inserted!";
            }
            vertex->setSelected(true);
        }

        for (std::pair<int,int> p : edges) {
            Vertex<std::string> *originVertex = g->idFindVertex(p.first);
            if (originVertex == nullptr) {
                return "Invalid AvoidSegment inserted!";
            }
            if (originVertex->isSelected()) {
                continue;
            }
            for (auto e : originVertex->getAdj()) {
                if (e->getDest()->getId() == p.second) {
                    e->setSelected(true);
                    break;
                }
            }
            return "Invalid AvoidSegment inserted!";
        }
        result.append(driveRestrictedRoute(g,originVertex,destVertex,vertex,edges,middle));
        return result;
    }


    else if(mode == "driving-walking") {
        //wip

    }
    return "";
}
