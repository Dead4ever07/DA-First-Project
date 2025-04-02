#ifndef ROUTESEARCH_H
#define ROUTESEARCH_H
#include "Graph.h"


/**
 * @brief Constructs the driving route from the destination to the origin based on the shortest path computed.
 *
 * This function traces back the shortest path from the destination to the origin using the path set by dijkstra().
 * It stores the sequence of vertex IDs in the route vector and accumulates the total driving cost.
 * If the function is being used for non-restricted driving paths (toSelect flag is enable), it marks visited vertices as selected to prevent
 * them from being reused in the alternative route.
 * The firstPath is enabled when the last item shouldn't be included, which happens when there's an IncludeNode in the restricted route. When this function is called
 * for the second time, it avoids adding middle vertex in the vector twice.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param route Reference to a vector that will store the sequence of vertex IDs in the computed path.
 * @param cost Reference to an integer that will store the total cost of the computed path.
 * @param toSelect Boolean flag indicating whether to mark the vertices and edges in the path as selected (to avoid using it in the alternative route).
 * @param firstPath Boolean flag indicating whether this is the first path being computed (to avoid duplicate values in the restricted route, when including a node).
 *
 * @note Time Complexity: O(V) since it traces back through at most all vertices in the path.
 */
void getDriveRoute(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath);

/**
 * @brief Retrieves the shortest path from origin to destination using Dijkstra's algorithm.
 *
 * This function is responsible for retrieving the shortest path computed by Dijkstra’s algorithm. It first
 * calls dijkstra() to check if there are paths are available, from the origin to the destination. If no path
 * exists it returns false, otherwise, it retrieves the computed route and cost using getDriveRoute()
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param route Reference to a vector that will store the sequence of vertex IDs in the computed path.
 * @param cost Reference to an integer that will store the total cost of the computed path.
 * @param toSelect Boolean flag indicating whether to mark the vertices and edges as selected (to avoid using it in the alternative route).
 * @param firstPath Boolean flag indicating whether this is the first path being computed (to avoid duplicate selections when including a node).
 * @return True if a valid path is found, false otherwise.
 *
 * @note Time Complexity: O((V + E)log V), since it calls dijkstra(), where V is the number of vertices and E is the number of edges.
 */
bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath);

/**
 * This function generates a formatted string with the expected result
 *
 * @param route Vector of vertex IDs representing the computed route.
 * @param routeCost The total cost of the computed route.
 * @return True if successful, false otherwise.
 *
 * @note Time Complexity: O(V), where V is the number of vertices. This is the shortest path, so the size of the route vector is at most |V| - 1.
 */
std::string printRoute(const std::vector<int> &route, int routeCost);

/**
 * @brief This function computes the shortest driving route between two vertices using
 * Dijkstra’s algorithm. It also attempts to find an alternative route, if possible.
 *
 * This function computes the best driving route from an origin vertex to a destination vertex. It first calls
 * getPath() to determine the shortest path. If a path is found the function attempts to find an alternative
 * route by calling getPath() again. If no alternative route is found, it appends "none" to the result. Otherwise,
 * it formats and adds the alternative route.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the source vertex.
 * @param dest Pointer to the destination vertex.
 * @return A formatted string containing the best and alternative routes.
 *
 * @note Time Complexity: O((V + E)log V) since it calls getPath() which executes dijkstra(). V is the number of vertices and E is the number of edges.
 */
std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest);

/**
 * @brief This function computes the shortest restricted driving route between two vertices using Dijkstra’s algorithm.
 *
 * This function computes the best driving route from an origin to a destination vertex, while considering an optional
 * middle vertex. If no middle vertex is specified, it finds the shortest driving route by calling getPath(). If a
 * middle vertex is provided, it ensures that the route passes through it. The computed route and its cost are
 * formatted into a string.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param middle The ID of the middle vertex that must be included in the route (-1 if not required).
 * @return A formatted string containing the restricted driving route and its cost. If no route is found, "none" is returned.
 *
 * @note Time Complexity: O((V + E)log V) due to Dijkstra’s algorithm being used within getPath(). V is the number of vertices and E is the number of edges.
 */
std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& middle);

#endif //ROUTESEARCH_H
