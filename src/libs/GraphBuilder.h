#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"

/**
 * This function reads distance data from a file and adds edges to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param distances Path to the file containing distances between locations.
 * @note Time Complexity: O(E), where E is the number of edges in the file
 */
void graphDistance(Graph<std::string>* g, std::string distances);

/**
 * This function reads location data from a file and adds vertices to the graph.
 *
 * @param g Pointer to the Graph object.
 * @param locations Path to the file containing location data.
 * @note Time Complexity: O(V), where V is the number of vertices in the file.
 */
void graphLocation(Graph<std::string>* g, std::string locations);

/**
 * This function visits each vertice and iterates through all its adjacent edges, marking both as not selected.
 *
 * @param g Pointer to the graph.
 *
 * @note Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 */
void deselect(Graph<std::string>*g);

#endif //GRAPHBUILDER_H
