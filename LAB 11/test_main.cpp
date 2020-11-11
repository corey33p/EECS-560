// # include "myGraph_corey33p.hpp"
# include "myGraph.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
      std::cout << "You have to provide one test instance file to run the test main!\n";
      return 0;
  }
  myGraph* g = new myGraph(argv[1]);
  g->print2();
  std::cout << "\n";
  for(int s=0; s < 500; s++)
  {
  g->dijkstra(s);
  std::cout << "\n";
  for(int i = 0; i < 500 ; i++)
  {
    g->printPath(i);
    std::cout << "\n" << g->computePathCost(i) << "\n";
  }
  }
  delete g;
  return 0;
}