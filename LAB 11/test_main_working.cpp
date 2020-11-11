# include "myGraph.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "\n\n\nYou have to provide one test instance file to run the test main!\n\n\n\n";
        std::cout << "\n\n\nYou have to provide one test instance file to run the test main!\n\n\n\n";
        return 0;
    }
    bool debug = false;
    bool debug2 = false;
    myGraph* g = new myGraph(argv[1]);
    if (debug) cerr<<"check1"<<endl;
    g->print2();
    if (debug) cerr<<"check2"<<endl;
    std::cout << "\n";
    for(int s=0; s < 500; s++){
        if (s<g->graphSize()){
            if (debug2) cerr<<"s: "<<s<<endl;
            g->dijkstra(s);
            std::cout << "\n";
            for(int i = 0; i < 500 ; i++){
                if (i<g->graphSize()){
                    g->printPath(i);
                    if (debug) cerr<<"check4"<<endl;
                    std::cout << "\n" << g->computePathCost(i) << "\n";
                    if (debug) cerr<<"check5"<<endl;
                }
            }
        }
    }
    delete g;

    return 0;
}