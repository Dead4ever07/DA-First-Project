#include "libs/RouteSearch.h"
#include "libs/DijkstraFunctions.h"


void getDriveRoute(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath) {
    if (!firstPath) {
        route.push_back(dest->getId());
    }

    if (toSelect) {
        dest->getPath()->setSelected(true);
    }
    cost += dest->getPath()->getDriving();
    dest = dest->getPath()->getOrig();


    while (dest != origin) {
        int vertexId = dest->getId();
        cost += dest->getPath()->getDriving();
        if (toSelect) {
            dest->setSelected(true);
            dest->getPath()->setSelected(true);
        }
        dest = dest->getPath()->getOrig();
        route.push_back(vertexId);
    }


    route.push_back(origin->getId());
}


bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath) {

    dijkstra(g,origin,dest);

    if (dest->getPath() == nullptr) {
        return false;
    }

    getDriveRoute(g,origin,dest,route,cost,toSelect,firstPath);

    return true;
}


std::string printRoute(const std::vector<int> &route,const int routeCost) {
    std::string result = std::to_string(route[route.size()-1]);
    for (int i = route.size()-2; i >= 0; i--) {
        result.append("," + std::to_string(route[i]));
    }
    result.append("(" + std::to_string(routeCost) + ")\n");
    return result;
}


std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest){

    std::string result = "BestDrivingRoute:";

    std::vector<int> bestRoute;
    int bestRouteCost = 0;

    if (!getPath(g,origin,dest,bestRoute, bestRouteCost,true,false)) {
        result.append("none\nAlternativeDrivingRoute:none\n");
        return result;
    }

    result.append(printRoute(bestRoute,bestRouteCost));

    result.append("AlternativeDrivingRoute:");

    std::vector<int> alternativeRoute;
    int alternativeRouteCost = 0;

    if (!getPath(g,origin,dest,alternativeRoute, alternativeRouteCost,true,false)) {
        result.append("none\n");
    }
    else {
        result.append(printRoute(alternativeRoute,alternativeRouteCost));
    }
    return result;
}

std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& middle) {

    std::string result = "RestrictedDrivingRoute:";

    int cost = 0;
    std::vector<int> route;

    if (middle == -1) {
        if (!getPath(g,origin,dest,route,cost,false,false)) {
            result.append("none\n");
        }
        else {
            result.append(printRoute(route,cost));
        }
        return result;
    }
    Vertex<std::string>* middleVertex = g->idFindVertex(middle);

    if (!getPath(g,middleVertex,dest,route,cost,false,false) || !getPath(g,origin,middleVertex,route,cost,false,true)) {
        result.append("none\n");
        return result;
    }

    result.append(printRoute(route,cost));

    return result;
}
