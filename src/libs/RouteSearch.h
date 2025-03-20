
#ifndef ROUTESEARCH_H
#define ROUTESEARCH_H
#include "Graph.h"

bool relaxCar(Edge<std::string> *edge);

bool relaxWalking(Edge<std::string> *edge);

void dijkstraWalking(Graph<std::string> *g, Vertex<std::string> *origin, int maxWalkingDist);

void dijkstra(Graph<std::string> *g, Vertex<std::string> *origin,Vertex<std::string> *dest);

bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool isRestricted, bool firstPath);

std::string printRoute(const std::vector<int> &route, int routeCost);

std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest);

std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& middle);

std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& max);

#endif //ROUTESEARCH_H
