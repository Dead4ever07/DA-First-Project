
#ifndef ROUTESEARCH_H
#define ROUTESEARCH_H
#include "Graph.h"

bool relaxCar(Edge<int> *edge);

void dijkstra(Graph<int> * g, const int &origin);

bool getPath(Graph<int> * g, const int &origin, const int& dest,std::vector<int> &route, int &cost);

void printRoute(const std::vector<int> &route, int routeCost);

void driveRoute(Graph<int> * g, const int &origin, const int& dest);

#endif //ROUTESEARCH_H
