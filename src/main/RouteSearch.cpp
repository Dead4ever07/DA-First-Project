#include "libs/RouteSearch.h"

bool relaxCar(Edge<std::string> *edge) { // d[u] + driv(u,v) < d[v]
    Vertex<std::string> *src = edge->getOrig();
    Vertex<std::string> *dst = edge->getDest();

    if (edge->getDriving() == -1 || edge->isSelected() || dst->isSelected()) {
        return false;
    }

    if (dst->getDist() > src->getDist() + edge->getDriving()) {
        dst->setDist(src->getDist() + edge->getDriving());
        dst->setPath(edge);
        return true;
    }
    return false;
}

bool relaxWalking(Edge<std::string> *edge) {
    Vertex<std::string> *src = edge->getOrig();
    Vertex<std::string> *dst = edge->getDest();

    if (edge->isSelected() || dst->isSelected()) {
        return false;
    }

    if (dst->getDist() > src->getDist() + edge->getWalking()) {
        dst->setDist(src->getDist() + edge->getWalking());
        dst->setForwardPath(edge);
        return true;
    }
    return false;
}

void dijkstraWalking(Graph<std::string> *g, Vertex<std::string> *origin, int maxWalkingDist) {

    MutablePriorityQueue<Vertex<std::string>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setForwardPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    origin->setDist(0);
    q.insert(origin);
    origin->setVisited(true);

    while (!q.empty()) {
        Vertex<std::string> *vertex = q.extractMin();
        if (vertex->getDist() >= maxWalkingDist) {
            return;
        }
        for (Edge<std::string> *edge : vertex->getAdj()) {
            if(relaxWalking(edge)) {
                if (!edge->getDest()->isVisited()) {
                    edge->getDest()->setVisited(true);
                    q.insert(edge->getDest());
                }
                else {
                    q.decreaseKey(edge->getDest());
                }
            }
        }

    }
}

void dijkstra(Graph<std::string> *g, Vertex<std::string> *origin,Vertex<std::string> *dest) {

    MutablePriorityQueue<Vertex<std::string>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    origin->setDist(0);
    q.insert(origin);
    origin->setVisited(true);

    while (!q.empty()) {
        Vertex<std::string> *vertex = q.extractMin();
        if (dest != nullptr && vertex == dest) {
            return;
        }
        for (Edge<std::string> *edge : vertex->getAdj()) {
            if(relaxCar(edge)) {
                if (!edge->getDest()->isVisited()) {
                    edge->getDest()->setVisited(true);
                    q.insert(edge->getDest());
                }
                else {
                    q.decreaseKey(edge->getDest());
                }
            }
        }

    }
}

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

void getDriveRoute(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool isRestricted, bool firstPath) {
    //to avoid repeating the same vertex in restricted path when I call getPath(g,middle,dest,route,cost,true,false) -> getPath(g,origin,middle,route,cost,true,true)
    if (!firstPath) {
        route.push_back(dest->getId());
    }

    cost += dest->getPath()->getDriving();
    dest = dest->getPath()->getOrig();

    while (dest != origin) {
        int vertexId = dest->getId();
        cost += dest->getPath()->getDriving();
        //in restricted paths I can repeat the vertices of the first/last graph
        if (!isRestricted) {
            dest->setSelected(true);
        }
        dest = dest->getPath()->getOrig();
        route.push_back(vertexId);
    }

    route.push_back(origin->getId());
}

bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool isRestricted, bool firstPath) {

    dijkstra(g,origin,dest);

    if (dest->getPath() == nullptr) {
        return false;
    }

    getDriveRoute(g,origin,dest,route,cost,isRestricted,firstPath);

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

    if (!getPath(g,origin,dest,bestRoute, bestRouteCost,false,false)) {
        result.append("none\nAlternativeDrivingRoute:none\n");
        return result;
    }

    result.append(printRoute(bestRoute,bestRouteCost));

    result.append("AlternativeDrivingRoute:");

    std::vector<int> alternativeRoute;
    int alternativeRouteCost = 0;

    if (!getPath(g,origin,dest,alternativeRoute, alternativeRouteCost,false,false)) {
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
        if (!getPath(g,origin,dest,route,cost,true,false)) {
            result.append("none\n");
        }
        else {
            result.append(printRoute(route,cost));
        }
        return result;
    }
    Vertex<std::string>* middleVertex = g->idFindVertex(middle);

    if (!getPath(g,middleVertex,dest,route,cost,true,false) || !getPath(g,origin,middleVertex,route,cost,true,true)) {
        result.append("none\n");
        return result;
    }

    result.append(printRoute(route,cost));

    return result;
}


std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& max) {
    std::string result = "DrivingRoute:";
    dijkstraWalking(g,dest,max);
    std::vector<Vertex<std::string>*> parkingSpots;
    for (auto temp : g->getVertexSet()) {
        if (temp->getDist() <= max && temp->isParking()) {
            temp->setForwardDist(temp->getDist());
            parkingSpots.push_back(temp);
        }
    }

    if (parkingSpots.empty()) {
        return "DrivingRoute:none\nParkingNode:none\nWalkingRoute:none\nTotalTime:\nMessage:No possible route with max. walking time of "+std::to_string(max) + " minutes.";
    }

    dijkstra(g,origin,nullptr);
    int distance = INF;
    Vertex<std::string> *parkingVertex = nullptr;
    for (auto temp : parkingSpots) {
        if ((temp->getDist() + temp->getForwardDist() < distance) || ((temp->getDist() + temp->getForwardDist() == distance) && parkingVertex != nullptr && temp->getForwardDist() > parkingVertex->getForwardDist())) {
            distance = temp->getDist() + temp->getForwardDist();
            parkingVertex = temp;
        }
    }

    //não tenho ainda certeza da parte dos erros !!!
    if (parkingVertex == nullptr) {
        return "DrivingRoute:none\nParkingNode:none\nWalkingRoute:none\nTotalTime:\nMessage:No possible route with max. walking time of "+std::to_string(max) + " minutes.";
    }

    std::vector<int> drivingRoute;
    int drivingRouteCost = 0;

    std::vector<int> walkRoute;
    int walkRouteCost = 0;

    getDriveRoute(g,origin,parkingVertex,drivingRoute,drivingRouteCost,true,false);
    result.append(printRoute(drivingRoute,drivingRouteCost));

    result.append("ParkingNode:" + std::to_string(parkingVertex->getId()));
    result.append("\nWalkingRoute:");

    getWalkRoute(g,parkingVertex,dest,walkRoute,walkRouteCost);
    std::ranges::reverse(walkRoute);
    result.append(printRoute(walkRoute,walkRouteCost));

    result.append("TotalTime:");
    result.append(std::to_string(distance));

    return result;

}