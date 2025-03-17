#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include <sstream>

#include "libs/GraphBuilder.h"
#include "../libs/Menu.h"

int main() {
    /*
    Graph<std::string>* g = new Graph<std::string>();

    graphLocation(g, "../resources/SmallLocations.csv");
    graphDistance(g, "../resources/SmallDistances.csv");

    driveRoute(g,3,8);
    */
    /*
    readInput("input.txt");
    */
    Menu menu;
    menu.init();
    menu.run();
    return 0;
}