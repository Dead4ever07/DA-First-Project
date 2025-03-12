#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include <sstream>

#include "../libs/Graph.h"
#include "libs/RouteSearch.h"

int main() {

    Graph<std::string>* g = new Graph<std::string>();

    g->addVertex(1, "a", "10", false);
    g->addVertex(2, "b", "20", false);
    g->addVertex(3, "c", "30", false);
    g->addVertex(4, "d", "40", false);
    g->addVertex(5, "e", "50", false);
    g->addVertex(6, "f", "60", false);
    g->addVertex(7, "g", "70", false);

    g->addEdge("10", "20", 3, 0);
    g->addEdge("10", "50", 5, 0);
    g->addEdge("20", "50", 10, 0);
    g->addEdge("20", "60", 2, 0);
    g->addEdge("30", "40", 1, 0);
    g->addEdge("50", "60", 2, 0);
    g->addEdge("50", "70", 6, 0);
    g->addEdge("60", "30", 4, 0);
    g->addEdge("60", "70", 8, 0);
    g->addEdge("70", "40", 8, 0);

    driveRoute(g,1,4);


    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.