# include "myGraph.hpp"
# include <iostream>
# include <vector>
# include <string>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "You have to provide one test instance file to run the test main!\n";
        return 0;
    }

    // Declear a traverse graph object
    myGraph* g = new myGraph(argv[1]);

    // print out the adjacency list
    g->print();
    std::cout << "\n";

    // start search from some vertices
    for(int i = 0; i < 1000; i+=23)
    {
        if (i< (int) g->graphSize()){
            g->BFS(i);
            std::cout << "\n";
            g->DFS(i);
            std::cout << "\n";
        }
    }


    delete g;
    return 0;
}