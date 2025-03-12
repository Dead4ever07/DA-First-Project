
#ifndef ROUTESEARCH_H
#define ROUTESEARCH_H
#include "Graph.h"

bool relaxCar(Edge<std::string> *edge);

void dijkstra(Graph<std::string> * g, const int &origin);

bool getPath(Graph<std::string> * g, const int &origin, const int& dest,std::vector<int> &route, int &cost);

void printRoute(const std::vector<int> &route, int routeCost);

void driveRoute(Graph<std::string> * g, const int &origin, const int& dest);

#endif //ROUTESEARCH_H
