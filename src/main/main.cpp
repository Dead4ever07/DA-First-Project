#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include <sstream>

#include "../libs/Graph.h"
#include "libs/RouteSearch.h"

int main() {

    Graph<int> g;

    g.addVertex(1,"a", "10",false);
    g.addVertex(2,"b", "20",false);
    g.addVertex(3,"c", "30",false);
    g.addVertex(4,"d", "40",false);
    g.addVertex(5,"e", "50",false);
    g.addVertex(6,"f", "60",false);
    g.addVertex(7,"g", "70",false);

    g.addEdge(1, 2, 3,0);
    g.addEdge(1, 5, 5,0);
    g.addEdge(2, 5, 10,0);
    g.addEdge(2, 6, 2,0);
    g.addEdge(3, 4, 1,0);
    g.addEdge(5, 6, 2,0);
    g.addEdge(5, 7, 6,0);
    g.addEdge(6, 3, 4,0);
    g.addEdge(6, 7, 8,0);
    g.addEdge(7, 4, 8,0);

    int origin = 1;
    int dest = 4;
    driveRoute(&g,origin,dest);

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.