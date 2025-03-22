#include "libs/RouteSearch.h"
#include <stdint.h>
#include <limits.h>

/**
 * @brief Relaxes an edge in the graph for driving mode.
 *
 * This function checks whether an edge can provide a shorter path to its destination vertex. It compares
 * the current shortest known distance to the destination with the potential new distance by going through
 * the considered edge. If the new distance is smaller, it updates the destination vertex with the new distance
 * and sets the path to come from the considered edge. The function returns true if an update was made, otherwise,
 * it returns false
 *
 * @param edge Pointer to the edge being considered for relaxation.
 * @return True if the edge was relaxed, false otherwise.
 *
 * @note Time Complexity: O(1), since it performs a constant number of operations.
 */
bool relaxCar(Edge<std::string> *edge) { // d[u] + driv(u,v) < d[v]
    Vertex<std::string> *src = edge->getOrig();
    Vertex<std::string> *dst = edge->getDest();

    if (edge->getDriving() == -1 || edge->isSelected() || dst->isSelected()) {
        return false;
    }

    if (dst->getDist() > src->getDist() + edge->getDriving()) {
        dst->setDist(src->getDist() + edge->getDriving());
        dst->setPath(edge);
        return true;
    }
    return false;
}

bool relaxWalking(Edge<std::string> *edge) {
    Vertex<std::string> *src = edge->getOrig();
    Vertex<std::string> *dst = edge->getDest();

    if (edge->isSelected() || dst->isSelected()) {
        return false;
    }

    if (dst->getDist() > src->getDist() + edge->getWalking()) {
        dst->setDist(src->getDist() + edge->getWalking());
        dst->setForwardPath(edge);
        return true;
    }
    return false;
}

void dijkstraWalking(Graph<std::string> *g, Vertex<std::string> *origin) {

    MutablePriorityQueue<Vertex<std::string>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setForwardPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    origin->setDist(0);
    q.insert(origin);
    origin->setVisited(true);

    while (!q.empty()) {
        Vertex<std::string> *vertex = q.extractMin();
        for (Edge<std::string> *edge : vertex->getAdj()) {
            if(relaxWalking(edge)) {
                if (!edge->getDest()->isVisited()) {
                    edge->getDest()->setVisited(true);
                    q.insert(edge->getDest());
                }
                else {
                    q.decreaseKey(edge->getDest());
                }
            }
        }

    }
}

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
void dijkstra(Graph<std::string> *g, Vertex<std::string> *origin,Vertex<std::string> *dest) {

    MutablePriorityQueue<Vertex<std::string>> q;

    for (auto temp : g->getVertexSet()) {
        temp->setPath(nullptr);
        temp->setDist(INF);
        temp->setVisited(false);
    }

    origin->setDist(0);
    q.insert(origin);
    origin->setVisited(true);

    while (!q.empty()) {
        Vertex<std::string> *vertex = q.extractMin();
        if (dest != nullptr && vertex == dest) {
            return;
        }
        for (Edge<std::string> *edge : vertex->getAdj()) {
            if(relaxCar(edge)) {
                if (!edge->getDest()->isVisited()) {
                    edge->getDest()->setVisited(true);
                    q.insert(edge->getDest());
                }
                else {
                    q.decreaseKey(edge->getDest());
                }
            }
        }

    }
}

void getWalkRoute(Graph<std::string> *g, Vertex<std::string>* middle, Vertex<std::string>* dest,std::vector<int> &route, int &cost) {

    route.push_back(middle->getId());

    cost += middle->getForwardPath()->getWalking();
    middle = middle->getForwardPath()->getOrig();

    while (middle != dest) {
        int vertexId = middle->getId();
        cost += middle->getForwardPath()->getWalking();
        middle = middle->getForwardPath()->getOrig();
        route.push_back(vertexId);
    }

    route.push_back(middle->getId());
}

void getDriveRoute(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath) {
    if (!firstPath) {
        route.push_back(dest->getId());
    }

    if (toSelect) {
        dest->getPath()->setSelected(true);
    }
    cost += dest->getPath()->getDriving();
    dest = dest->getPath()->getOrig();


    while (dest != origin) {
        int vertexId = dest->getId();
        cost += dest->getPath()->getDriving();
        if (toSelect) {
            dest->setSelected(true);
            dest->getPath()->setSelected(true);
        }
        dest = dest->getPath()->getOrig();
        route.push_back(vertexId);
    }


    route.push_back(origin->getId());
}

/**
 * @brief Retrieves the shortest path from origin to destination.
 *
 * This function is responsible for retrieving the shortest path computed by Dijkstra’s algorithm. It first
 * calls dijkstra() to check if there are paths are available, from the origin to the destination. If no path
 * exists it returns false, otherwise, it reconstructs the path by following the stored edges backward from the
 * destination to the origin, storing the visited vertices in a route vector while also accumulating the total
 * cost. If the function is being used for restricted paths, it marks visited vertices as selected to prevent
 * them from being reused in further computations.
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the source vertex.
 * @param dest Pointer to the destination vertex.
 * @param route Reference to a vector where the computed path will be stored.
 * @param cost Reference to an integer storing the total cost of the path.
 * @param isRestricted Whether the path is restricted.
 * @param firstPath Indicates whether this is the first segment of a restricted path.
 * @return True if a valid path is found, false otherwise.
 *
 * @note Time Complexity: O((V + E)log V), since it calls dijkstra().
 */
bool getPath(Graph<std::string> *g, Vertex<std::string>* origin, Vertex<std::string>* dest,std::vector<int> &route, int &cost, bool toSelect, bool firstPath) {

    dijkstra(g,origin,dest);

    if (dest->getPath() == nullptr) {
        return false;
    }

    getDriveRoute(g,origin,dest,route,cost,toSelect,firstPath);

    return true;
}

/**
 * This function generates a formatted string with the expected result
 *
 * @param route Vector of vertex IDs representing the computed route.
 * @param routeCost The total cost of the computed route.
 * @return A formatted string representing the route.
 *
 * @note Time Complexity: O(N), where N is the number of nodes in the route.
 */
std::string printRoute(const std::vector<int> &route,const int routeCost) {
    std::string result = std::to_string(route[route.size()-1]);
    for (int i = route.size()-2; i >= 0; i--) {
        result.append("," + std::to_string(route[i]));
    }
    result.append("(" + std::to_string(routeCost) + ")\n");
    return result;
}

/**
 * @brief This function computes the shortest driving route between two vertices using
 * Dijkstra’s algorithm. It also attempts to find an alternative route, if possible.
 *
 * This function computes and returns the best driving route from an origin vertex to a destination vertex.
 * It first calls getPath to determine the shortest path. If a path is found the function attempts to find
 * an alternative route by calling getPath again. If no alternative route is found, it appends "none" to
 * the result. Otherwise, it formats and adds the alternative route.
 *
 *
 * @param g Pointer to the graph.
 * @param origin Pointer to the source vertex.
 * @param dest Pointer to the destination vertex.
 * @return A formatted string containing the best and alternative routes.
 *
 * @note Time Complexity: O((V + E) log V) since it calls getPath() which executes dijkstra().
 */
std::string driveRoute(Graph<std::string> * g, Vertex<std::string>* origin, Vertex<std::string>* dest){

    std::string result = "BestDrivingRoute:";

    std::vector<int> bestRoute;
    int bestRouteCost = 0;

    if (!getPath(g,origin,dest,bestRoute, bestRouteCost,true,false)) {
        result.append("none\nAlternativeDrivingRoute:none\n");
        return result;
    }

    result.append(printRoute(bestRoute,bestRouteCost));

    result.append("AlternativeDrivingRoute:");

    std::vector<int> alternativeRoute;
    int alternativeRouteCost = 0;

    if (!getPath(g,origin,dest,alternativeRoute, alternativeRouteCost,true,false)) {
        result.append("none\n");
    }
    else {
        result.append(printRoute(alternativeRoute,alternativeRouteCost));
    }
    return result;
}

std::string driveRestrictedRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest,const int& middle) {

    std::string result = "RestrictedDrivingRoute:";

    int cost = 0;
    std::vector<int> route;


    if (middle == -1) {
        if (!getPath(g,origin,dest,route,cost,false,false)) {
            result.append("none\n");
        }
        else {
            result.append(printRoute(route,cost));
        }
        return result;
    }
    Vertex<std::string>* middleVertex = g->idFindVertex(middle);

    if (!getPath(g,middleVertex,dest,route,cost,false,false) || !getPath(g,origin,middleVertex,route,cost,false,true)) {
        result.append("none\n");
        return result;
    }

    result.append(printRoute(route,cost));

    return result;
}

Vertex<std::string> * driveWalkingPath(std::vector<Vertex<std::string>*> &parkingSpots, int &distance) {
    Vertex<std::string> *parkingVertex = nullptr;

    for (auto vertex : parkingSpots) {
        bool moreEcologic = (vertex->getDist() + vertex->getForwardDist() == distance) && (parkingVertex == nullptr || vertex->getDist() < parkingVertex->getDist());
        if (vertex->getDist() + vertex->getForwardDist() < distance || moreEcologic) {
            distance = vertex->getDist() + vertex->getForwardDist();
            parkingVertex = vertex;
        }
    }
    return parkingVertex;
}

std::pair<Vertex<std::string>*,Vertex<std::string> *> driveWalkingPaths(std::vector<Vertex<std::string>*> &parkingSpots, int &distance1, int &distance2) {
    Vertex<std::string> *parkingVertex1 = nullptr;
    Vertex<std::string> * parkingVertex2 = nullptr;

    for (auto vertex : parkingSpots) {

        bool moreEcologic1 = (vertex->getDist() + vertex->getForwardDist() == distance1) && (parkingVertex1 == nullptr || vertex->getDist() < parkingVertex1->getDist());
        bool moreEcologic2 = (vertex->getDist() + vertex->getForwardDist() == distance2) && (parkingVertex2 == nullptr || vertex->getDist() < parkingVertex2->getDist());

        if (vertex->getDist() + vertex->getForwardDist() < distance1 || moreEcologic1) {
            distance2 =distance1;
            parkingVertex2 = parkingVertex1;
            distance1 = vertex->getDist() + vertex->getForwardDist();
            parkingVertex1 = vertex;
        }
        else if (vertex->getDist() + vertex->getForwardDist() < distance2 || moreEcologic2) {
            distance2 = vertex->getDist() + vertex->getForwardDist();
            parkingVertex2 = vertex;
        }
    }
    return {parkingVertex1,parkingVertex2};
}

std::string printWalkingDrivingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* parkingVertex,Vertex<std::string>* dest, std::string numRoute, int distance) {
    std::string result = "DrivingRoute"+ numRoute +":";
    std::vector<int> drivingRoute;
    int drivingRouteCost = 0;

    std::vector<int> walkRoute;
    int walkRouteCost = 0;


    getDriveRoute(g,origin,parkingVertex,drivingRoute,drivingRouteCost,false,false);
    result.append(printRoute(drivingRoute,drivingRouteCost));

    result.append("ParkingNode"+ numRoute +":" + std::to_string(parkingVertex->getId()));
    result.append("\nWalkingRoute"+ numRoute +":");

    getWalkRoute(g,parkingVertex,dest,walkRoute,walkRouteCost);
    std::ranges::reverse(walkRoute);
    result.append(printRoute(walkRoute,walkRouteCost));

    result.append("TotalTime"+ numRoute +":");
    result.append(std::to_string(distance) + '\n');

    return result;
}


std::string approximateSolution(Graph<std::string> * g,Vertex<std::string>* origin,Vertex<std::string>* dest, std::vector<Vertex<std::string>*> parkingSpots) {
    std::string result = "";
    int distance1 = INT_MAX;
    int distance2 = INT_MAX;



    std::pair<Vertex<std::string>*,Vertex<std::string> *> parkingVertexes = driveWalkingPaths(parkingSpots,distance1,distance2);

    Vertex<std::string>* parkingVertex1 = parkingVertexes.first;
    Vertex<std::string> *parkingVertex2 = parkingVertexes.second;


    if (parkingVertex1 == nullptr) {
        result.append("Its impossible to create an approximate solution\n");
        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex1,dest,"1",distance1));


    if (parkingVertex2 == nullptr) {
        result.append("Its impossible to create a second approximate solution\n");
        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex2,dest,"2",distance2));

    return result;
}


std::string driveWalkingRoute(Graph<std::string> * g,Vertex<std::string>* origin, Vertex<std::string>* dest, const int& max) {

    std::string result = "";
    dijkstraWalking(g,dest);

    std::vector<Vertex<std::string>*> parkingSpots;
    std::vector<Vertex<std::string>*> requirementParkingSpots;

    for (auto temp : g->getVertexSet()) {
        if (temp->getDist() != INT_MAX && temp->isParking() && temp != origin && temp != dest) {
            temp->setForwardDist(temp->getDist());
            parkingSpots.push_back(temp);
            if (temp->getDist() <= max) {
                requirementParkingSpots.push_back(temp);
            }
        }
    }


    if (requirementParkingSpots.empty()) {
        //ver com a prof!!!
        //result.append("DrivingRoute:none\nParkingNode:none\nWalkingRoute:none\nTotalTime:\nMessage:No possible route with max. walking time of "+std::to_string(max) + " minutes.\n");

        dijkstra(g,origin,nullptr);

        result.append(approximateSolution(g,origin,dest,parkingSpots));

        result.append("Message:No possible route with max. walking time of "+std::to_string(max) + " minutes.");

        return result;
    }

    dijkstra(g,origin,nullptr);

    int distance = INT_MAX;
    Vertex<std::string> *parkingVertex = driveWalkingPath(requirementParkingSpots,distance);

    if (parkingVertex == nullptr) {



        result.append(approximateSolution(g,origin,dest,parkingSpots));

        result.append("Message:The parking spot(s) within the maximum walking distance have no driving route to them.");

        return result;
    }

    result.append(printWalkingDrivingRoute(g,origin,parkingVertex,dest,"",distance));

    return result;

}