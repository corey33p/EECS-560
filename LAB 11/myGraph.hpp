#include <algorithm>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class myGraph{
    public:
        myGraph(){
            nodeList.push_back(new Node(0));
        }
        myGraph( std::string fileName ){
            nodeList.push_back(new Node(0));
            ifstream file(fileName);
            if (!file.good()) {
                cout<<"Bad filename."<<endl;
                return;
            }
            char c1,c2,c3; // to eat the commas
            int sourceNodeNumber,destinationNodeNumber,distance;
            struct distItem {
                distItem(int s,int de,int di): source{ s },destination{ de },distance{ di }{}
                int source;
                int destination;
                int distance;
            };
            vector<distItem> distances;
            while (file >> sourceNodeNumber >> c1 >> destinationNodeNumber >> c2 >> distance >> c3){
                while (sourceNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                while (destinationNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                while (sourceNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                nodeList[sourceNodeNumber]->adjacencyList.push_back((nodeList[destinationNodeNumber]));
                distances.push_back(distItem(sourceNodeNumber,destinationNodeNumber,distance));
            }
            for (auto node : nodeList)
                node->distances = vector<int>(nodeList.size(),0);
            while (!distances.empty()){
                distItem d = distances.back();
                distances.pop_back();
                nodeList[d.source]->distances[d.destination]=d.distance;
            }
            // int i = 0;
            // for (auto node : nodeList){
            //     cerr<<i<<":";
            //     for (auto distance : node->distances) {
            //         if (distance != 0){
            //             cerr<<" "<<distance;
            //         }
            //     }
            //     cerr<<endl;
            //     i++;
            // }
        }
        ~myGraph(){
            for (auto node : nodeList){
                delete node;
                node = nullptr;
            }
        }
        void print(){
            int i = 0;
            for (auto node : nodeList){
                cout<<i<<":";
                for (auto destNode : node->adjacencyList) {
                    cout<<" "<<destNode->number;
                }
                cout<<endl;
                i++;
            }
        }
        void print2(){
            int i = 0;
            for (auto node : nodeList){
                cout<<i<<":";
                for (auto distance : node->distances) {
                    if (distance != 0){
                        cout<<" "<<distance;
                    }
                }
                cout<<endl;
                i++;
            }
        }
        void BFS(int source){
            nodeQueue = new queue<Node*>;
            nodeQueue->push(nodeList[source]);
            nodeList[source]->visited = true;
            BFS_backend();
            delete nodeQueue;
            nodeQueue = nullptr;
            resetVisited();
        }
        void DFS(int source){
            nodeStack = new stack<Node*>;
            nodeStack->push(nodeList[source]);
            nonRecursive_DFS();
            delete nodeStack;
            nodeStack = nullptr;
            resetVisited();
        }
        void dijkstra(int source){
            reset();
            dijkstra_backend(source); // using queue

            // reset();
            // nodeList[source]->minDistance = 0;
            // dijkstra_backend(); // without queue

        }
        void printPath(int destination){
            stack<int> path;
            path.push(destination);
            Node *currNode = nodeList[destination];
            Node *prevNode = currNode->path;
            while (prevNode != nullptr){
                path.push(prevNode->number);
                currNode = nodeList[prevNode->number];
                prevNode = currNode->path;
            }
            if (!path.empty()){
                cout<<path.top();
                path.pop();
            }
            while (!path.empty()){
                cout<<" "<<path.top();
                path.pop();
            }
            // cout<<endl;
        }
        int computePathCost(int destination){
            int cost = 0;
            Node *currNode = nodeList[destination];
            Node *prevNode = currNode->path;
            while (prevNode != nullptr){
                cost+=prevNode->distances[currNode->number];
                currNode = nodeList[prevNode->number];
                prevNode = currNode->path;
            }
            return cost;
        }
        void dk_print(){
            for (auto node : nodeList){
                cout<<node->number<<"-"<<node->minDistance<<endl;
            }
        }
        int graphSize(){
            return nodeList.size();
        }
    private:
        struct Node {
            Node(int n): number{ n }{}
            Node(int n,vector<Node*> adjList): number{ n },adjacencyList(adjList){}
            ~Node() {}
            bool visited = false;
            int number;
            int minDistance = 2147483647;
            // int pathLength = 0;
            Node *path = nullptr;
            vector<Node*> adjacencyList;
            vector<int> distances;
            // int getDistance(int nodeNumber){
            //     int index = 0;
            //     for (auto node : adjacencyList){
            //         if (node->number == nodeNumber) {
            //             return distances[index];
            //         }
            //         index++;
            //     }
            //     throw invalid_argument("\n\ngetDistance(): Node number " + to_string(nodeNumber) + " not found in adjacencyList.\n\n");
            //     return 0;
            // }
        };
        struct PQNode {
            PQNode(int num,int dist): number{ num },minDistance{ dist }{}
            int number;
            int minDistance;
        };
        // struct CompareDist {
        //     bool operator()(Node* lhs, Node* rhs) {
        //         return lhs->minDistance > rhs->minDistance;
        //      }
        //  };
        struct CompareDist {
            bool operator()(PQNode lhs, PQNode rhs) {
                if (lhs.minDistance >= rhs.minDistance){
                    if (lhs.minDistance == rhs.minDistance){
                        return lhs.number > rhs.number;
                    } else {
                        return lhs.minDistance > rhs.minDistance;
                    }
                }
                return lhs.minDistance > rhs.minDistance;
             }
         };
        vector<Node*> nodeList;
        queue<Node*> *nodeQueue = nullptr;
        stack<Node*> *nodeStack = nullptr;
        //
        void BFS_backend(){
            while (!nodeQueue->empty()){
                Node *currNode = nodeQueue->front();
                nodeQueue->pop();
                cout<<currNode->number<<endl;
                for (auto destNode : currNode->adjacencyList){
                    if (!destNode->visited){
                        nodeQueue->push(destNode);
                        destNode->visited=true;
                    }
                }
            }
        }
        void nonRecursive_DFS(){
            while (!nodeStack->empty()){
                Node *currNode = nodeStack->top();
                nodeStack->pop();
                if (!currNode->visited){
                    cout<<currNode->number<<endl;
                    currNode->visited = true;
                }

                // iterate the adjacent nodes backwards
                for (auto destNode = currNode->adjacencyList.rbegin(); destNode != currNode->adjacencyList.rend(); ++destNode){
                    if (!(*destNode)->visited){
                        nodeStack->push((*destNode));
                    }
                }
            }
        }
        void dijkstra_backend(int source){
            // cerr<<"using queue"<<endl;
            nodeList[source]->minDistance = 0;
            Node *startNode = nodeList[source];
            // priority_queue<Node*,vector<Node*>,CompareDist> nodeQueue;
            priority_queue<PQNode,vector<PQNode>,CompareDist> nodeQueue;
            nodeQueue.push(PQNode(startNode->number,0));
            int i = 0;
            while (!nodeQueue.empty()){
                int minNodeNumber = nodeQueue.top().number;
                nodeQueue.pop();
                Node *minNode = nodeList[minNodeNumber];
                while (minNode->visited && !nodeQueue.empty()){
                    minNodeNumber = nodeQueue.top().number;
                    nodeQueue.pop();
                    minNode = nodeList[minNodeNumber];
                }
                if (minNode->visited) return;
                // cerr<<"source: "<<source<<endl;
                minNode->visited=true;
                for (auto destNode : minNode->adjacencyList){
                    if (!destNode->visited){
                        int newDistance = minNode->minDistance + minNode->distances[destNode->number];
                        if (newDistance < destNode->minDistance){
                            destNode->minDistance = newDistance;
                            destNode->path = minNode;
                            nodeQueue.push(PQNode(destNode->number,newDistance));
                        }
                    }
                }
                i++;
                // debug_print(minNode);
            }
        }
        void dijkstra_backend(){
            // cerr<<"not using queue"<<endl;
            while (1){
                bool changed = false;
                Node* minNode;
                int minDist=2147483647;
                for (auto currNode : nodeList){
                    if (currNode->minDistance < minDist && !(currNode->visited)){
                        minDist = currNode->minDistance;
                        minNode = currNode;
                        changed = true;
                    }
                }
                minNode->visited = true;
                if (!changed) return;
                for (auto destNode : minNode->adjacencyList){
                    if (!destNode->visited){
                        int newDistance = minNode->minDistance + minNode->distances[destNode->number];
                        if (newDistance < destNode->minDistance){
                            destNode->minDistance = newDistance;
                            destNode->path = minNode;
                        }
                    }
                }
                // debug_print(minNode);
            }
        }
        void reset(){
            for (auto node : nodeList){
                node->visited = false;
                node->minDistance = 2147483647;
                node->path = nullptr;
                if (nodeList.size() != node->distances.size()){
                    node->distances.resize(graphSize(),0);
                }
            }
        }
        void resetVisited(){
            for (auto node : nodeList){
                node->visited = false;
            }
        }
        void debug_print(Node* node){
            cerr<<"node number "<<node->number<<endl;
            cerr<<"node adjacency list:    ";
            for (auto destNode : node->adjacencyList){
                cerr<<" "<<destNode->number;
            }
            cerr<<endl<<"node weights tentative: ";
            for (auto weight : node->distances){
                cerr<<" "<<node->minDistance+weight;
            }
            cerr<<endl<<"node weights actual:    ";
            for (auto neighbor : node->adjacencyList){
                cerr<<" "<<neighbor->minDistance;
            }
            cerr<<endl<<endl;
        }
};
