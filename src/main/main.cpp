#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
#include "../libs/Graph.h"
#include "libs/GraphBuilder.h"

void dfs(Vertex<int>* source)
{
      Vertex<int>* v = source;
      v->setVisited(true);
      std::cout<<v->getInfo()<<' '<<std::endl;
      for(auto e : v->getAdj())
      {
           Vertex<int>* w = e->getDest();
           if(!w->isVisited())
           {
                dfs(w);
           }
      }
}



int main() {

    Graph<int> g;

    for(int i = 1; i <= 6; i++)
        g.addVertex(i);

    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(2, 4, 3);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 6, 2);
    g.addEdge(5, 6, 3);

    dfs(g.getVertexSet().front());


    graphDistance( "C:\\Users\\teres\\Documents\\2A2S\\DA\\DA-First-Project\\resources\\Distances.csv");
    graphLocation( "C:\\Users\\teres\\Documents\\2A2S\\DA\\DA-First-Project\\resources\\Locations.csv");

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.