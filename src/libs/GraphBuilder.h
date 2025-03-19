//
// Created by luis-santos on 2/27/25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"

/**
 * @brief It fills the graph with the information provided.
 * @param[out] g The name of the reservoir.
 * @param[in] Distances The file name were the edges are stores.
 * @param[in] Locations The file name were the vertices are stored.
 */

void graphDistance(Graph<std::string>* g, std::string distances);

void graphLocation(Graph<std::string>* g, std::string locations);

Graph<std::string> * createGraph();

void readInput(Graph<std::string>* g, std::string input);

std::string checkInput(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle, std::string mode);











#endif //GRAPHBUILDER_H
