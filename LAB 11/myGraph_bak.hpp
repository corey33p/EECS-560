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
            while (file >> sourceNodeNumber >> c1 >> destinationNodeNumber >> c2 >> distance >> c3){
                while (sourceNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                while (destinationNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                nodeList[sourceNodeNumber]->adjacencyList.push_back((nodeList[destinationNodeNumber]));
                nodeList[sourceNodeNumber]->distances.push_back(distance);
            }
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
                    cout<<" "<<distance;
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
            // Node *startNode = nodeList[source];
            // PQNode pqn = PQNode(startNode->number,0);
            // priority_queue<Node*,vector<Node*>,CompareDist> nodeQueue;
            // priority_queue<PQNode,vector<PQNode>,CompareDist> nodeQueue;
            // queue<int> nodeQueue;
            // nodeQueue.push(PQNode(startNode->number,2147483647));
            // nodeQueue.push(startNode);
            nodeList[source]->minDistance = 0;
            dijkstra_backend();
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
                cost+=prevNode->getDistance(currNode->number);
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
            int getDistance(int nodeNumber){
                int index = 0;
                for (auto node : adjacencyList){
                    if (node->number == nodeNumber) {
                        return distances[index];
                    }
                    index++;
                }
                throw invalid_argument("\n\ngetDistance(): Node number " + to_string(nodeNumber) + " not found in adjacencyList.\n\n");
                return 0;
            }
        };
        struct PQNode {
            PQNode(int num,int dist): number{ num },minDistance{ dist }{}
            int number;
            int minDistance;
        };
        struct CompareDist {
            bool operator()(Node* lhs, Node* rhs) {
                return lhs->minDistance >= rhs->minDistance;
             }
         };
        // struct CompareDist {
        //     bool operator()(PQNode lhs, PQNode rhs) {
        //         return lhs.minDistance < rhs.minDistance;
        //      }
        //  };
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
        // void dijkstra_backend(priority_queue<Node*,vector<Node*>,CompareDist> nodeQueue){
        //     while (!nodeQueue.empty()){
        //         // int currNodeNumber = nodeQueue.top().number;
        //         // Node *currNode = nodeList[currNodeNumber];
        //         Node *currNode = nodeQueue.top();
        //         while (currNode == nodeQueue.top() && !nodeQueue.empty())
        //             nodeQueue.pop();
        //         for (auto destNode : currNode->adjacencyList){
        //             int newDistance;
        //             if (currNode->minDistance != 2147483647)
        //                 newDistance = currNode->minDistance + currNode->getDistance(destNode->number);
        //             else
        //                 newDistance = currNode->getDistance(destNode->number);
        //             bool visitNode = false;
        //             if (newDistance < destNode->minDistance)
        //                 visitNode = true;
        //             if (visitNode){
        //                 destNode->minDistance = newDistance;
        //                 destNode->path = currNode;
        //                 // std::make_heap(const_cast<Node**>(&nodeQueue.top()),
        //                 //    const_cast<Node**>(&nodeQueue.top()) + nodeQueue.size(),
        //                 //    CompareDist());
        //                 nodeQueue.push(destNode);
        //             }
        //         }
        //         // debug_print(currNode);
        //     }
        // }
        void dijkstra_backend(){
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
                        int newDistance = minNode->minDistance + minNode->getDistance(destNode->number);
                        if (newDistance < destNode->minDistance){
                            destNode->minDistance = newDistance;
                            destNode->visited = false;
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
                // node->pathLength = 0;
            }
        }
        void resetVisited(){
            for (auto node : nodeList){
                node->visited = false;
            }
        }
        void debug_print(Node* node){
            cerr<<"node number "<<node->number<<endl;
            cerr<<"node adjacency list: ";
            for (auto destNode : node->adjacencyList){
                cerr<<" "<<destNode->number;
            }
            cerr<<endl<<"node weights:        ";
            for (auto weight : node->distances){
                cerr<<" "<<node->minDistance+weight;
            }
            cerr<<endl<<endl;
        }
};
