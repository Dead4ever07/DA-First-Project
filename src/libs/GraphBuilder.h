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

/**
 * This function opens the specified file, reads its contents into a string, and
 * then calls readInputFromString() to process the data.
 *
 * @param g Pointer to the graph object.
 * @param fileName Name of the file containing input data.
 * @param output Reference to a string where the output result will be stored.
 *
 * @note Time Complexity: O(C + (V+E)log(V)), where:
 *   - C is the number of characters in the input file.
 *   - (V+E)log(V) is the complexity of checkInput(), called by readInputFromString().
 */
void readInputFromFile(Graph<std::string>* g, std::string fileName, std::string& output);

/**
 * This function reads an input string containing route parameters and processes them.
 * After extracting the information, it calls checkInput() to validate the processed data.
 *
 * @param g Pointer to the graph object.
 * @param input The input string containing route configuration.
 * @param output Reference to a string where the output result will be stored.
 *
 * @note Time Complexity: O(C + (V+E)log(V)), where:
 *   - C is the number of characters in the input string.
 *   - (V+E)log(V) is the complexity of checkInput().
 */
void readInputFromString(Graph<std::string>*g, std::string input, std::string& output);

std::string checkInput(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges,const int& middle, std::string mode);











#endif //GRAPHBUILDER_H
