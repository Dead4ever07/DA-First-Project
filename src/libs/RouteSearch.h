
#ifndef ROUTESEARCH_H
#define ROUTESEARCH_H
#include "Graph.h"

bool relaxCar(Edge<std::string> *edge);

void dijkstra(Graph<std::string> *g, Vertex<std::string> *origin,Vertex<std::string> *dest);

bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool isRestricted, bool firstPath);

std::string printRoute(const std::vector<int> &route, int routeCost);

std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest);

std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle);

#endif //ROUTESEARCH_H
