#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include <sstream>

#include "../libs/Graph.h"
#include "libs/RouteSearch.h"

int main() {

    Graph<std::string> g;

    g.addVertex(1,"a", "10",false);
    g.addVertex(2,"b", "20",false);
    g.addVertex(3,"c", "30",false);
    g.addVertex(4,"d", "40",false);
    g.addVertex(5,"e", "50",false);
    g.addVertex(6,"f", "60",false);
    g.addVertex(7,"g", "70",false);



    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.