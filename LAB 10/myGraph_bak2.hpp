// #include <algorithm> //vector.begin(), vector.end()
// #include <array>
#include <iostream>
#include <fstream>
// #include <math.h>
// #include <sstream>
// #include <stdexcept>
// #include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

class myGraph{
    public:
        myGraph(){
            adjacencyList = new vector<vector<Node>>;
            adjacencyList->push_back(vector<Node>());
        }
        myGraph( std::string fileName ){
            adjacencyList = new vector<vector<Node>>;
            adjacencyList->push_back(vector<Node>());
            ifstream file(fileName);
            if (!file.good()) {
                cout<<"Bad filename."<<endl;
                return;
            }
            int sourceNodeNumber,destinationNodeNumber;
            char c1,c2; // to eat the commas
            while (file >> sourceNodeNumber >> c1 >> destinationNodeNumber >> c2){
                while (sourceNodeNumber >= (int) adjacencyList->size()) {
                    adjacencyList->push_back(vector<Node>());
                }
                (*adjacencyList)[sourceNodeNumber].push_back(Node(destinationNodeNumber));
            }
        }
        ~myGraph(){
            delete adjacencyList;
            adjacencyList = nullptr;
        }
        void print(){
            int i = 0;
            for (auto list : (*adjacencyList)){
                cout<<i<<": ";
                for (auto destNode : list) {
                    cout<<destNode.number<<" ";
                }
                cout<<endl;
                i++;
            }
        }
        void BFS(int source){
            // visited = new vector<bool>(adjacencyList->size(),false);
            nodeQueue = new queue<Node>;
            nodeQueue->push(source);
            // (*visited)[source]=true;
            BFS_backend();
            // BFS_backend(source);
            // delete visited;
            // visited = nullptr;
            delete nodeQueue;
            nodeQueue = nullptr;
            resetVisited();
        }
        void DFS(int source){
            // visited = new vector<bool>(adjacencyList->size(),false);
            // visitedCount = new int(0);
            nodeStack = new stack<Node>;
            nodeStack->push(source);
            nonRecursive_DFS();
            // DFS_backend(source);
            // delete visited;
            // visited = nullptr;
            // delete visitedCount;
            // visitedCount = nullptr;
            resetVisited();
        }
        int graphSize(){
            if (adjacencyList == nullptr)
                return 0;
            else
                return adjacencyList->size();
        }
    private:
        struct Node {
            Node(int n): number{ n }{}
            // Node(int n,vector<*Node> adjList): number{ n },adjacencyList(adjList){}
            bool visited = false;
            int number ;
            // vector<*Node> adjacencyList;
        };
        vector<*Node> *adjacencyList;
        queue<Node> *nodeQueue = nullptr;
        stack<Node> *nodeStack = nullptr;
        // int *visitedCount = nullptr;
        //
        void BFS_backend(){
            if ((int) nodeQueue->size() == 0) return;
            while (!nodeQueue->empty()){
                Node currNode = nodeQueue->front();
                nodeQueue->pop();
                cout<<currNode.number<<endl;
                for (auto destNode : (*adjacencyList)[currNode.number]){
                    if (!destNode.visited){
                        nodeQueue->push(destNode);
                        destNode.visited=true;
                    }
                }
            }
        }
        //
        // below is similar to textbook implementation...
        // O(n^2) = no thanks
        // simplified Dijkstra's algorithm
        //
        // void BFS_backend(int startNode){
        //     vector<int> distances;
        //     for (unsigned int i = 0;i < adjacencyList.size();i++){
        //         distances.push_back(-1);
        //     }
        //     distances[startNode]=0;
        //     for (unsigned int currDist = 0; currDist < adjacencyList.size(); currDist++){
        //         for (unsigned int currNode = 0; currNode < adjacencyList.size(); currNode++){
        //             if (!(*visited)[currNode] && distances[currNode]==(int)currDist){
        //                 (*visited)[currNode] = true;
        //                 for (auto destNode : adjacencyList[currNode]){
        //                     if (distances[destNode]==-1){
        //                         cout<<currNode<<endl;
        //                         distances[destNode]=currDist + 1;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        //
        // recursive DFS, which is apparently unsuited for
        // ridiculously large graphs due to stack overflow errors
        //
        // void DFS_backend(int node){
        //     (*visited)[node]=true;
        //     cout<<node<<endl;
        //     (*visitedCount)++;
        //     if (*visitedCount == graphSize()) return;
        //     for (auto destination : (*adjacencyList)[node]){
        //         if (!visited->at(destination)){
        //             DFS_backend(destination);
        //         }
        //     }
        // }
        void nonRecursive_DFS(){
            if ((int) nodeQueue->size() == 0) return;
            while (!nodeQueue->empty()){
                Node currNode = nodeStack->top();
                nodeQueue->pop();
                cout<<currNode.number<<endl;

                // iterate the adjacent nodes backwards
                for (auto destNode = (*adjacencyList)[currNode.number].rbegin(); destNode != (*adjacencyList)[currNode.number].rend(); ++destNode){
                    if (!(*destNode).visited){
                        nodeStack->push((*destNode));
                        (*destNode).visited=true;
                    }
                }
            }
        }
        void resetVisited(){
            for (auto node : adjacencyList){
                node.visited = false;
            }
        }
};
