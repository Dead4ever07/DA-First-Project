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

void readInput(std::string input);











#endif //GRAPHBUILDER_H
