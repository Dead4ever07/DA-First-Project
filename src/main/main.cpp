#include <iostream>

#include <sstream>

#include "../libs/Graph.h"
#include "libs/GraphBuilder.h"
#include "libs/RouteSearch.h"

int main() {

    Graph<std::string>* g = new Graph<std::string>();

    graphLocation(g, "../resources/SmallLocations.csv");
    graphDistance(g, "../resources/SmallDistances.csv");

    driveRoute(g,3,8);

    return 0;
}
