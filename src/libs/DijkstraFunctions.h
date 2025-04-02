#ifndef DIJKSTRAFUNCTIONS_H
#define DIJKSTRAFUNCTIONS_H

#include "Graph.h"


/**
 * @brief Relaxes an edge in the graph for driving mode.
 *
 * This function checks whether an edge can provide a shorter path to its destination vertex, without taking
 * walking path into consideration. It compares the current shortest known distance to the destination with
 * the potential new distance by going through the considered edge. If the new distance is smaller, it updates
 * the destination vertex with the new distance and sets the path to come from the considered edge. The function
 * returns true if an update was made and false otherwise.
 *
 * @param edge Pointer to the edge being considered for relaxation.
 * @return True if the edge was relaxed, false otherwise.
 *
 * @note Time Complexity: O(1), since it performs a constant number of operations.
 */
bool relaxCar(Edge<std::string> *edge);

/**
 * @brief Relaxes an edge based on walking distance.
 *
 * This function checks if the walking distance through the given edge provides a shorter path to
 * the destination vertex. It compares the current shortest known distance to the destination with
 * the potential new distance by going through the considered edge. If the new distance is smaller,
 * it updates the destination vertex with the new distance and sets the path to come from the considered
 * edge. The function returns true if an update was made and false otherwise.
 *
 * @param edge Pointer to the edge being considered for relaxation.
 * @return True if the edge was relaxed, false otherwise.
 *
 * @note Time Complexity: O(1), since it performs a constant number of operations.
 */
bool relaxWalking(Edge<std::string> *edge);

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path, but uses the relaxWalking() function to update distances to use walking paths.
 *
 * This function implements Dijkstra’s algorithm to find the shortest path from a starting vertex
 * to a destination vertex, using walking paths. It initializes all vertices by setting their distances to infinity and
 * marking them as unvisited. The starting vertex is given a distance of zero and added to a priority
 * queue. The algorithm then repeatedly extracts the vertex with the smallest distance from the queue
 * and relaxes all its adjacent edges. If relaxing an edge improves the known distance to a neighboring
 * vertex, that vertex is either added to the queue or updated if it is already in the queue. The process
 * continues until all reachable vertices have been processed or the destination vertex is reached. If the
 * destination is unreachable, its node has no path and its distance remains infinity.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex for the shortest path computation.
 *
 * @note Time Complexity: O((V + E)log V), where:
 *   - V is the number of vertices.
 *   - E is the number of edges.
 *   - Extracting the minimum and updating keys in Priority Queue cost O(log V)
 *   - Extracting the minimum is executed O(V) times
 *   - Keys are updated O(E) times
 *   - Therefore the overall complexity is O((V + E)log V)
 */
void dijkstraWalking(Graph<std::string> *g, Vertex<std::string> *origin);

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path.
 *
 * This function implements Dijkstra’s algorithm to find the shortest path from a starting vertex
 * to a destination vertex. It initializes all vertices by setting their distances to infinity and
 * marking them as unvisited. The starting vertex is given a distance of zero and added to a priority
 * queue. The algorithm then repeatedly extracts the vertex with the smallest distance from the queue
 * and relaxes all its adjacent edges. If relaxing an edge improves the known distance to a neighboring
 * vertex, that vertex is either added to the queue or updated if it is already in the queue. The process
 * continues until all reachable vertices have been processed or the destination vertex is reached. If the
 * destination is unreachable, its node has no path and its distance remains infinity.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the source vertex.
 * @param dest Pointer to the destination vertex.
 *
 * @note Time Complexity: O((V + E)log V), where:
 *   - V is the number of vertices.
 *   - E is the number of edges.
 *   - Extracting the minimum and updating keys in Priority Queue cost O(log V)
 *   - Extracting the minimum is executed O(V) times
 *   - Keys are updated O(E) times
 *   - Therefore the overall complexity is O((V + E)log V)
 */
void dijkstra(Graph<std::string> *g, Vertex<std::string> *origin,Vertex<std::string> *dest);

#endif //DIJKSTRAFUNCTIONS_H
