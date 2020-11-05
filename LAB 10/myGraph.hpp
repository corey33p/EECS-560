// #include <algorithm> //vector.begin(), vector.end()
// #include <array>
#include <iostream>
#include <fstream>
// #include <math.h>
// #include <sstream>
// #include <stdexcept>
// #include <string>
#include <queue>
#include <vector>
using namespace std;

class myGraph{
    public:
        myGraph(){
            sourceNodes = new vector<vector<int>>;
            sourceNodes->push_back(vector<int>());
        }
        myGraph( std::string fileName ){
            sourceNodes = new vector<vector<int>>;
            sourceNodes->push_back(vector<int>());
            ifstream file(fileName);
            if (!file.good()) {
                cout<<"Bad filename."<<endl;
                return;
            }
            int sourceNodeNumber,destinationNodeNumber;
            char c1,c2; // to eat the commas
            while (file >> sourceNodeNumber >> c1 >> destinationNodeNumber >> c2){
                while (sourceNodeNumber >= (int) sourceNodes->size()){
                    sourceNodes->push_back(vector<int>());
                }
                (*sourceNodes)[sourceNodeNumber].push_back(destinationNodeNumber);
            }
        }
        ~myGraph(){
            delete sourceNodes;
            sourceNodes = nullptr;
        }
        void print(){
            int i = 0;
            for (auto adjacencyList : (*sourceNodes)){
                cout<<i<<": ";
                for (auto destNode : adjacencyList) {
                    cout<<destNode<<" ";
                }
                cout<<endl;
                i++;
            }
        }
        void BFS(int source){
            visited = new vector<bool>(sourceNodes->size(),false);
            nodeQueue = new queue<int>;
            nodeQueue->push(source);
            (*visited)[source]=true;
            BFS_backend();
            // BFS_backend(source);
            delete visited;
            visited = nullptr;
            delete nodeQueue;
            nodeQueue = nullptr;
            return;
        }
        void DFS(int source){
            visited = new vector<bool>(sourceNodes->size(),false);
            visitedCount = new int(0);
            DFS_backend(source);
            delete visited;
            visited = nullptr;
            delete visitedCount;
            visitedCount = nullptr;
            return;
        }
        int graphSize(){
            if (sourceNodes == nullptr)
                return 0;
            else
                return sourceNodes->size();
        }
    private:
        vector<vector<int>> *sourceNodes = nullptr;
        vector<bool> *visited = nullptr;
        queue<int> *nodeQueue = nullptr;
        int *visitedCount = nullptr;
        //
        void BFS_backend(){
            if ((int) nodeQueue->size() == 0) return;
            while (!nodeQueue->empty()){
                int currNode = nodeQueue->front();
                nodeQueue->pop();
                cout<<currNode<<endl;
                for (auto destNode : (*sourceNodes)[currNode]){
                    if (!(*visited)[destNode]){
                        nodeQueue->push(destNode);
                        (*visited)[destNode]=true;
                    }
                }
            }
        }
        //
        // below is similar to textbook implementation...
        //
        // void BFS_backend(int startNode){
        //     vector<int> distances;
        //     for (unsigned int i = 0;i < sourceNodes.size();i++){
        //         distances.push_back(-1);
        //     }
        //     distances[startNode]=0;
        //     for (unsigned int currDist = 0; currDist < sourceNodes.size(); currDist++){
        //         for (unsigned int currNode = 0; currNode < sourceNodes.size(); currNode++){
        //             if (!(*visited)[currNode] && distances[currNode]==(int)currDist){
        //                 (*visited)[currNode] = true;
        //                 for (auto destNode : sourceNodes[currNode]){
        //                     if (distances[destNode]==-1){
        //                         cout<<currNode<<endl;
        //                         distances[destNode]=currDist + 1;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        void DFS_backend(int node){
            (*visited)[node]=true;
            cout<<node<<endl;
            (*visitedCount)++;
            if (*visitedCount == graphSize()) return;
            for (auto destination : (*sourceNodes)[node]){
                if (!visited->at(destination)){
                    DFS_backend(destination);
                }
            }
        }
};
