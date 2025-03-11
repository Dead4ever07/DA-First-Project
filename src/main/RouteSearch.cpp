#include "libs/RouteSearch.h"

bool relaxCar(Edge<int> *edge) { // d[u] + driv(u,v) < d[v]
    if (edge->getDriving() == -1) {
        return false;
    }
    Vertex<int> *src = edge->getOrig();
    Vertex<int> *dst = edge->getDest();
    if (dst->getDist() > src->getDist() + edge->getDriving()) {
        dst->setDist(src->getDist() + edge->getDriving());
        dst->setPath(edge);
        return true;
    }
    return false;
}

void dijkstra(Graph<int> *g, const int &origin) {

    MutablePriorityQueue<Vertex<int>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    auto ini = g->findVertex(origin);
    ini->setDist(0);
    q.insert(ini);
    ini->setVisited(true);
    while (!q.empty()) {
        Vertex<int> *vertex = q.extractMin();

        for (Edge<int> *edge : vertex->getAdj()) {
            if(relaxCar(edge)) {
                if (!edge->getDest()->isVisited()) {
                    q.insert(edge->getDest());
                }
                else {
                    q.decreaseKey(edge->getDest());
                }
            }
        }

    }
}

bool getPath(Graph<int> *g, const int &origin, const int& dest,std::vector<int> &route, int &cost) {

    dijkstra(g, origin);
    Vertex<int> *dst = g->findVertex(dest);

    if (dst->getPath() == nullptr) {
        return false;
    }

    cost += dst->getPath()->getDriving();
    route.push_back(dst->getInfo());
    dst = dst->getPath()->getOrig();

    while (dst->getInfo() != origin) {
        int vertexInfo = dst->getInfo();
        cost += dst->getPath()->getDriving();
        dst = dst->getPath()->getOrig();
        route.push_back(vertexInfo);
        g->removeVertex(vertexInfo);
    }
    route.push_back(origin);
    return true;
}

void printRoute(const std::vector<int> &route,const int routeCost) {
    std::cout << route[route.size()-1];
    for (int i = route.size()-2; i >= 0; i--) {
        std::cout << "," <<route[i];
    }
    std::cout << "(" << routeCost << ")" <<std::endl;
}


void driveRoute(Graph<int> * g, const int &origin, const int& dest){
    std::vector<int> bestRoute;
    int bestRouteCost = 0;

    std::cout << "Source:" << origin << std::endl;
    std::cout << "Destination:" << dest << std::endl;

    std::cout << "BestDrivingRoute:";
    if (!getPath(g,origin,dest,bestRoute, bestRouteCost)) {
        std::cout<<"none\n"<<std::endl;
        std::cout << "AlternativeDrivingRoute:none\n";
    }
    else {
        printRoute(bestRoute,bestRouteCost);
    }

    std::vector<int> alternativeRoute;
    int alternativeRouteCost = 0;

    std::cout << "AlternativeDrivingRoute:";
    if (!getPath(g,origin,dest,alternativeRoute, alternativeRouteCost)) {
        std::cout << "none\n";
    }
    else {
        printRoute(alternativeRoute,alternativeRouteCost);
    }
}