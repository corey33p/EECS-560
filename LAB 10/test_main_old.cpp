# include "myGraph.hpp"
# include <iostream>
# include <vector>
# include <string>

int main(int argc, char* argv[])
{
    bool debug = false;
    if(argc != 2)
    {
        std::cout << "You have to provide one test instance file to run the test main!\n";
        return 0;
    }
    if (debug) cerr<<"check1"<<endl;
    // Declear a traverse graph object
    myGraph* g = new myGraph(argv[1]);
    if (debug) cerr<<"check2"<<endl;
    // print out the adjacency list
    g->print();
    if (debug) cerr<<"check3"<<endl;
    std::cout << "\n";
    if (debug) cerr<<"check4"<<endl;
    // start search from some vertices
    for(int i = 0; i < 500; i++)
    {
        if (i< (int) g->graphSize()){
            if (debug) cerr<<"check4.1"<<endl;
            g->BFS(i);
            std::cout << "\n";
            if (debug) cerr<<"check4.2"<<endl;
            g->DFS(i);
            std::cout << "\n";
        }
    }
    // cout<<"check5"<<endl;

    delete g;
    // cout<<"check6"<<endl;
    return 0;
}
