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

void dijkstra(Graph<std::string> *g, const int &origin) {

    MutablePriorityQueue<Vertex<std::string>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    auto ini = g->idFindVertex(origin);
    ini->setDist(0);
    q.insert(ini);
    ini->setVisited(true);
    while (!q.empty()) {
        Vertex<std::string> *vertex = q.extractMin();

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

bool getPath(Graph<std::string> *g, const int &origin, const int& dest,std::vector<int> &route, int &cost) {

    dijkstra(g, origin);
    Vertex<std::string> *dst = g->idFindVertex(dest);

    if (dst->getPath() == nullptr) {
        return false;
    }

    cost += dst->getPath()->getDriving();
    route.push_back(dst->getId());
    dst = dst->getPath()->getOrig();

    while (dst->getId() != origin) {
        int vertexId = dst->getId();
        cost += dst->getPath()->getDriving();
        dst->setSelected(true);
        dst = dst->getPath()->getOrig();
        route.push_back(vertexId);
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


void driveRoute(Graph<std::string> * g, const int &origin, const int& dest){
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