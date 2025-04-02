#ifndef ECOLOGICALROUTESEARCH_H
#define ECOLOGICALROUTESEARCH_H
#include "Graph.h"


/**
 * @brief Constructs the driving-walking route from the destination to the origin based on the shortest path computed.
 *
 * This function traces back the shortest walking path from the middle vertex (parkingVertex) to the destination, using
 * the path set by dijkstraWalking().
 * It stores the sequence of vertex IDs in the route vector and accumulates the total driving cost.
 *
 * @param g Pointer to the graph.
 * @param middle Pointer to the vertex where the walking route starts.
 * @param dest Pointer to the destination vertex.
 * @param route Reference to a vector storing the sequence of vertex IDs in the walking path.
 * @param cost Reference to an integer storing the total walking cost.
 *
 * @note Time Complexity: O(V) since it traces back through at most all vertices in the path.
 */
void getWalkRoute(Graph<std::string> *g, Vertex<std::string>* middle, Vertex<std::string>* dest,std::vector<int> &route, int &cost);

/**
 * @brief Finds the optimal parking spot based on the shortest combined driving and walking distance.
 *
 * This function iterates through a list of potential parking spots and selects the best option in terms
 * of total distance (driving + walking). If two parking spots have the same total distance, the one with the
 * shorter driving distance is preferred (considered more eco-friendly). In the end, distance has the total
 * distance for the best parking spot.
 *
 * @param parkingSpots A vector containing pointers to potential parking spot vertices.
 * @param distance Reference to an integer storing the minimum found total distance. It gets updated to the best-found distance.
 * @return A pointer to the optimal parking vertex. If no parking spot is found, returns nullptr.
 *
 * @note Time Complexity: O(N), where N is the number of parking spots in the vector. N is at most V
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
 * @return A pair of pointers to the best and second-best parking vertices, respectively. A nullptr is returned for every missing parking spot.
 *
 * @note Time Complexity: O(N), where N is the number of parking spots and each vertex is checked once. N is at most V
 */
std::pair<Vertex<std::string>*,Vertex<std::string> *> driveWalkingPaths(std::vector<Vertex<std::string>*> &parkingSpots, int &distance1, int &distance2);

/**
 * @brief Formats a string with a driving-walking route from origin to destination, including a parking spot.
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
 * @note Time Complexity: O(V), since the function finds the driving and walking routes. Moreover, it reverses the walking route, before adding it to the result. V is the number of vertices.
 */
std::string printWalkingDrivingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* parkingVertex,Vertex<std::string>* dest, std::string numRoute, int distance);

/**
 * @brief Finds an approximate driving-walking route when an exact solution isn't available.
 *
 * This function attempts to find up to two parking spots that minimize the total travel distance
 * and generates two routes, if possible. First, it identifies the two shortest paths and their
 * corresponding parking spots using driveWalkingPaths(). If there are two valid parking spots,
 * it generates both routes using printWalkingDrivingRoute(). If there are no valid parking
 * spots, it returns an error message for each try.
 *
 * @param g Pointer to the graph representing the road network.
 * @param origin Pointer to the origin vertex.
 * @param dest Pointer to the destination vertex.
 * @param parkingSpots List of parking spots in the graph.
 * @return A formatted string containing the approximate driving-walking route(s) and/or an error message.
 *
 * @note Time Complexity: O((V + E)log V) due to searching for parking spots and generating routes requires using Dijkstra's algorithm. V is the number of vertices and E is the number of edges.
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
 * @note Time Complexity: O((V + E)log V) due to Dijkstra’s algorithm being used within dijkstraWalking() and dijkstra(). V is the number of vertices and E is the number of edges.
 */
std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& max);


#endif //ECOLOGICALROUTESEARCH_H
