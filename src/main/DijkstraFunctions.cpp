//
// Created by teres on 23/03/2025.
//
#include "libs/RouteSearch.h"
#include "libs/DijkstraFunctions.h"
#include <stdint.h>
#include <limits.h>


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

void dijkstraWalking(Graph<std::string> *g, Vertex<std::string> *origin) {

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