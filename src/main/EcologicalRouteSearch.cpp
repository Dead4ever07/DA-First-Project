#include "../libs/EcologicalRouteSearch.h"
#include "libs/Graph.h"
#include "libs/RouteSearch.h"
#include "libs/DijkstraFunctions.h"
#include <climits>


void getWalkRoute(Graph<std::string> *g, Vertex<std::string>* middle, Vertex<std::string>* dest,std::vector<int> &route, int &cost) {

    route.push_back(middle->getId());

    cost += middle->getForwardPath()->getWalking();
    middle = middle->getForwardPath()->getOrig();

    while (middle != dest) {
        int vertexId = middle->getId();
        cost += middle->getForwardPath()->getWalking();
        middle = middle->getForwardPath()->getOrig();
        route.push_back(vertexId);
    }

    route.push_back(middle->getId());
}

Vertex<std::string> * driveWalkingPath(std::vector<Vertex<std::string>*> &parkingSpots, int &distance) {
    Vertex<std::string> *parkingVertex = nullptr;

    for (auto vertex : parkingSpots) {
        bool moreEcologic = (vertex->getDist() + vertex->getForwardDist() == distance) && (parkingVertex == nullptr || vertex->getDist() < parkingVertex->getDist());
        if (vertex->getDist() + vertex->getForwardDist() < distance || moreEcologic) {
            distance = vertex->getDist() + vertex->getForwardDist();
            parkingVertex = vertex;
        }
    }
    return parkingVertex;
}

std::pair<Vertex<std::string>*,Vertex<std::string> *> driveWalkingPaths(std::vector<Vertex<std::string>*> &parkingSpots, int &distance1, int &distance2) {
    Vertex<std::string> *parkingVertex1 = nullptr;
    Vertex<std::string> * parkingVertex2 = nullptr;

    for (auto vertex : parkingSpots) {

        bool moreEcologic1 = (vertex->getDist() + vertex->getForwardDist() == distance1) && (parkingVertex1 == nullptr || vertex->getDist() < parkingVertex1->getDist());
        bool moreEcologic2 = (vertex->getDist() + vertex->getForwardDist() == distance2) && (parkingVertex2 == nullptr || vertex->getDist() < parkingVertex2->getDist());

        if (vertex->getDist() + vertex->getForwardDist() < distance1 || moreEcologic1) {
            distance2 =distance1;
            parkingVertex2 = parkingVertex1;
            distance1 = vertex->getDist() + vertex->getForwardDist();
            parkingVertex1 = vertex;
        }
        else if (vertex->getDist() + vertex->getForwardDist() < distance2 || moreEcologic2) {
            distance2 = vertex->getDist() + vertex->getForwardDist();
            parkingVertex2 = vertex;
        }
    }
    return {parkingVertex1,parkingVertex2};
}

std::string printWalkingDrivingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* parkingVertex,Vertex<std::string>* dest, std::string numRoute, int distance) {
    std::string result = "DrivingRoute"+ numRoute +":";
    std::vector<int> drivingRoute;
    int drivingRouteCost = 0;

    std::vector<int> walkRoute;
    int walkRouteCost = 0;


    getDriveRoute(g,origin,parkingVertex,drivingRoute,drivingRouteCost,false,false);
    result.append(printRoute(drivingRoute,drivingRouteCost));

    result.append("ParkingNode"+ numRoute +":" + std::to_string(parkingVertex->getId()));
    result.append("\nWalkingRoute"+ numRoute +":");

    getWalkRoute(g,parkingVertex,dest,walkRoute,walkRouteCost);
    std::ranges::reverse(walkRoute);
    result.append(printRoute(walkRoute,walkRouteCost));

    result.append("TotalTime"+ numRoute +":");
    result.append(std::to_string(distance) + '\n');

    return result;
}

std::string approximateSolution(Graph<std::string> * g,Vertex<std::string>* origin,Vertex<std::string>* dest, std::vector<Vertex<std::string>*> parkingSpots) {
    std::string result = "";
    int distance1 = INT_MAX;
    int distance2 = INT_MAX;

    std::pair<Vertex<std::string>*,Vertex<std::string> *> parkingVertexes = driveWalkingPaths(parkingSpots,distance1,distance2);

    Vertex<std::string>* parkingVertex1 = parkingVertexes.first;
    Vertex<std::string> *parkingVertex2 = parkingVertexes.second;

    if (parkingVertex1 == nullptr) {
        result.append("Its impossible to create an approximate solution\n");
        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex1,dest,"1",distance1));


    if (parkingVertex2 == nullptr) {
        result.append("Its impossible to create a second approximate solution\n");
        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex2,dest,"2",distance2));

    return result;
}

std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest, const int& max) {

    std::string result = "";
    dijkstraWalking(g,dest);

    std::vector<Vertex<std::string>*> parkingSpots;
    std::vector<Vertex<std::string>*> requirementParkingSpots;

    for (auto temp : g->getVertexSet()) {
        if (temp->getDist() != INF && temp->isParking() && temp != origin && temp != dest) {
            temp->setForwardDist(temp->getDist());
            parkingSpots.push_back(temp);
            if (temp->getDist() <= max) {
                requirementParkingSpots.push_back(temp);
            }
        }
    }

    dijkstra(g,origin,nullptr);

    if (requirementParkingSpots.empty()) {
        //ver com a prof!!!
        //result.append("DrivingRoute:none\nParkingNode:none\nWalkingRoute:none\nTotalTime:\nMessage:No possible route with max. walking time of "+std::to_string(max) + " minutes.\n");

        result.append(approximateSolution(g,origin,dest,parkingSpots));

        result.append("Message:No possible route with max. walking time of "+std::to_string(max) + " minutes.");

        return result;
    }


    int distance = INT_MAX;
    Vertex<std::string> *parkingVertex = driveWalkingPath(requirementParkingSpots,distance);

    if (parkingVertex == nullptr) {

        result.append(approximateSolution(g,origin,dest,parkingSpots));

        result.append("Message:The parking spot(s) within the maximum walking distance have no driving route to them.");

        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex,dest,"",distance));

    return result;

}