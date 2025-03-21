//
// Created by luis-santos on 2/27/25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"

/**
 * Reads distance data from a file and adds edges to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param distances Path to the file containing distances between locations.
 * @note Time Complexity: O(E), where E is the number of edges in the file
 */
void graphDistance(Graph<std::string>* g, std::string distances);

/**
 * Reads location data from a file and adds vertices to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param locations Path to the file containing location data.
 * @note Time Complexity: O(V), where V is the number of vertices in the file.
 */
void graphLocation(Graph<std::string>* g, std::string locations);

void deselect(Graph<std::string>*g);











#endif //GRAPHBUILDER_H
