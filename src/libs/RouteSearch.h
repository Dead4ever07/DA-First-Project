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
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param route Reference to a vector that will store the sequence of vertex IDs in the computed path.
 * @param cost Reference to an integer that will store the total cost of the computed path.
 * @param toSelect Boolean flag indicating whether to mark the vertices and edges in the path as selected (to avoid using it in the alternative route).
 * @param firstPath Boolean flag indicating whether this is the first path being computed (to avoid duplicate selections when including a node).
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
 * @note Time Complexity: O((V + E)log V), since it calls dijkstra().
 */
bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath);

/**
 * This function generates a formatted string with the expected result
 *
 * @param route Vector of vertex IDs representing the computed route.
 * @param routeCost The total cost of the computed route.
 * @return A formatted string representing the route.
 *
 * @note Time Complexity: O(N), where N is the number of nodes in the route.
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
 * @note Time Complexity: O((V + E)log V) since it calls getPath() which executes dijkstra().
 */
std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest);

/**
 * @brief This function computes the shortest restricted driving route between two vertices using Dijkstra’s algorithm.
 *
 * This function computes the best driving route from an origin to a destination origin vertex to a destination
 * vertex, while considering an optional middle vertex. If no middle vertex is specified, it finds the shortest
 * driving route by calling getPath(). If a middle vertex is provided, it ensures that the route passes through
 * it. The computed route and its cost are formatted into a string.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param middle The ID of the middle vertex that must be included in the route (-1 if not required).
 * @return A formatted string containing the restricted driving route and its cost. If no route is found, "none" is returned.
 *
 * @note Time Complexity: O((V + E)log V) due to Dijkstra’s algorithm being used within getPath().
 */
std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& middle);

/**
 * @brief Finds the optimal parking spot based on the shortest combined driving and walking distance.
 *
 * This function iterates through a list of parking spots and selects the one that minimizes the total
 * distance, which is the sum of the driving distance (getDist()) and the walking distance (getForwardDist()).
 * If two parking spots have the same total distance, the one with the shorter driving distance is preferred.
 *
 * @param parkingSpots A vector containing pointers to potential parking spot vertices.
 * @param distance Reference to an integer storing the minimum found total distance.
 *                 It gets updated to the best-found distance.
 * @return A pointer to the optimal parking vertex. If no parking spot is found, returns nullptr.
 *
 * @note Time Complexity: O(N), where N is the number of parking spots in the vector.
 */
Vertex<std::string>* driveWalkingPath(std::vector<Vertex<std::string>*> &parkingSpots,int &distance);

/**
 * @brief Determines the two best parking spots for a drive-walk route based on distance and eco-friendliness.
 *
 * This function iterates through a list of potential parking spots and selects the two best options in terms
 * of total distance (driving + walking). If two parking spots have the same total distance, the one with the
 * shorter driving distance is preferred (considered more eco-friendly). In the end, distance1 and distance2
 * have the total distances for the best and second-best parking spots, respectively.
 *
 * @param parkingSpots A vector containing pointers to candidate parking vertices.
 * @param distance1 Reference to an integer storing the total distance to the best parking spot.
 * @param distance2 Reference to an integer storing the total distance to the second-best parking spot.
 * @return A pair of pointers to the best and second-best parking vertices, respectively.
 *
 * @note Time Complexity: O(N), where N is the number of parking spots and each vertex is checked once.
 */
std::pair<Vertex<std::string>*,Vertex<std::string> *> driveWalkingPaths(std::vector<Vertex<std::string>*> &parkingSpots, int &distance1, int &distance2);

/**
 * @brief Formats a combined driving-walking route from origin to destination, including a parking spot.
 *
 * This function first determines the driving route from the origin to the selected parking spot and then
 * computes the walking route from the parking spot to the destination. The resulting information is formatted
 * as a string.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the origin vertex.
 * @param parkingVertex Pointer to the parking spot vertex.
 * @param dest Pointer to the destination vertex.
 * @param numRoute Identifier for multiple routes.
 * @param distance Total estimated time for the entire trip (driving + walking).
 * @return A formatted string describing the full route, including driving and walking segments.
 *
 * @note Time Complexity: O(V), since the function finds the driving and walking routes and reverses the walking route before adding it to the result.
 */
std::string printWalkingDrivingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* parkingVertex,Vertex<std::string>* dest, std::string numRoute, int distance);

/**
 * @brief Finds an approximate driving-walking route when an exact solution isn't available.
 *
 * This function attempts to find up to two parking spots that minimize the total travel distance
 * and generates two routes, if possible. First, it Identifies the two closest parking spots using
 * driveWalkingPaths(). If there are two valid parking spots, it generates both routes using
 * printWalkingDrivingRoute(). If no valid parking spots are available, it returns an error message
 * for each try.
 *
 * @param g Pointer to the graph representing the road network.
 * @param origin Pointer to the origin vertex.
 * @param dest Pointer to the destination vertex.
 * @param parkingSpots List of available parking spots in the graph.
 * @return A formatted string containing the approximate driving-walking route(s).
 *
 * @note Time Complexity: O((V + E)log V) due to searching for parking spots and generating routes requires using Dijkstra's algorithm.
 */
std::string approximateSolution(Graph<std::string> * g,Vertex<std::string>* origin,Vertex<std::string>* dest, std::vector<Vertex<std::string>*> parkingSpots);

/**
 * @brief Finds the best driving and walking route given a maximum walking distance constraint.
 *
 * This function first calls dijkstraWalking() with the destination to compute the shortest walking distances from
 * all potential parking spots. It then filters parking spots into parkingSpots, which contains all available parking
 * spots and requirementParkingSpots, which only contains the parking spots that are within the given max walking
 * distance. If no parking spots are within the max walking distance, an approximate solution is returned. Otherwise,
 * the best parking spot is selected using driveWalkingPath().
 *
 * @param g Pointer to the graph representing the road network.
 * @param origin Pointer to the starting vertex.
 * @param dest Pointer to the destination vertex.
 * @param max The maximum allowed walking time from the parking spot to the destination.
 * @return A formatted string describing the best possible route.
 *
 * @note Time Complexity: O((V + E)log V) due to Dijkstra’s algorithm being used within dijkstraWalking().
 */
std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& max);

#endif //ROUTESEARCH_H
