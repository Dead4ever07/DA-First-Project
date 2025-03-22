
#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include "Graph.h"

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

/**
 * @brief Validates user input and computes the appropriate route.
 *
 * This function checks if the given inputs exist in the graph. Then, it determines the appropriate
 * route computation based on the provided parameters. If the mode is "driving" with no constraints,
 * it computes the best and alternative driving routes. Otherwise, it calculates a restricted or a
 * driving-walking route.
 *
 * @param g Pointer to the graph.
 * @param origin The ID of the source vertex.
 * @param dest The ID of the destination vertex.
 * @param vertex A vector of node IDs that should be avoided.
 * @param edges A vector of pairs representing edges to be avoided.
 * @param middle The ID of a mandatory intermediate vertex (-1 if not required).
 * @param mode The selected travel mode ("driving" or "driving-walking").
 * @param maxWalkTime The maximum allowed walking time for mixed routes.
 * @return A formatted string containing the computed route or an error message if the input is invalid.
 *
 * @note Time Complexity: O((V + E) log V). The function may call driveRoute(), driveRestrictedRoute(),
 * or driveWalkingRoute(), each executing Dijkstra’s algorithm.
 */
std::string checkInput(Graph<std::string> * g, const int &origin, const int& dest, std::vector<int>& vertex, std::vector<std::pair<int,int>>& edges, int& middle, std::string mode, int maxWalkTime);

#endif //INPUTUTILS_H
