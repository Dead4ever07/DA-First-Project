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

void dijkstra(Graph<std::string> *g, const int &origin,const int &dest) {

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
        if (vertex->getId() == dest) {
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

//tirar o is restrictive!!!
bool getPath(Graph<std::string> *g, const int &origin, const int& dest,std::vector<int> &route, int &cost, bool isRestricted, bool firstPath) {

    dijkstra(g, origin,dest);
    Vertex<std::string> *dst = g->idFindVertex(dest);

    if (dst->getPath() == nullptr) {
        return false;
    }

    //to avoid repeating the same vertex in restricted path when I call getPath(g,middle,dest,route,cost,true,false) -> getPath(g,origin,middle,route,cost,true,true)
    if (!firstPath) {
        route.push_back(dest);
    }

    cost += dst->getPath()->getDriving();
    dst = dst->getPath()->getOrig();

    while (dst->getId() != origin) {
        int vertexId = dst->getId();
        cost += dst->getPath()->getDriving();
        //in restricted paths I can repeat the vertices of the first/last graph
        if (!isRestricted) {
            dst->setSelected(true);
        }
        dst = dst->getPath()->getOrig();
        route.push_back(vertexId);
    }

    route.push_back(origin);

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


std::string driveRoute(Graph<std::string> * g, const int &origin, const int& dest){

    std::string result = "Source:" + std::to_string(origin) + "\n" + "Dest:" + std::to_string(dest) + '\n' + "BestDrivingRoute:";

    std::vector<int> bestRoute;
    int bestRouteCost = 0;

    if (!getPath(g,origin,dest,bestRoute, bestRouteCost,false,false)) {
        result.append("none\nAlternativeDrivingRoute:none\n"); //!! ver complexidade de append e ver se faz mais sentido usar outra operação
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

std::string driveRestrictedRoute(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle) {

    for (const int id : vertex) {
        g->idFindVertex(id)->setSelected(true);
    }

    for (std::pair<int,int> p : edges) {
        Vertex<std::string> *originVertex = g->idFindVertex(p.first);
        if (originVertex == nullptr || originVertex->isSelected()) {
            continue;
        }
        for (auto e : originVertex->getAdj()) {
            if (e->getDest()->getId() == p.second) {
                e->setSelected(true);
                break;
            }
        }
    }

    std::string result = "Source:" + std::to_string(origin) + "\n" + "Dest:" + std::to_string(dest) + '\n' + "RestrictedDrivingRoute:";

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

    if (!getPath(g,middle,dest,route,cost,true,false) || !getPath(g,origin,middle,route,cost,true,true)) {
        result.append("none\n");
        return result;
    }

    result.append(printRoute(route,cost));

    return result;
}