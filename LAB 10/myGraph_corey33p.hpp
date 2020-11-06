#include <iostream>
#include <fstream>
#include <stack>
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
            int sourceNodeNumber,destinationNodeNumber;
            char c1,c2; // to eat the commas
            while (file >> sourceNodeNumber >> c1 >> destinationNodeNumber >> c2){
                while (sourceNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                while (destinationNodeNumber >= (int) nodeList.size()) {
                    nodeList.push_back(new Node(nodeList.size()));
                }
                nodeList[sourceNodeNumber]->adjacencyList.push_back((nodeList[destinationNodeNumber]));
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
                cout<<i<<": ";
                for (auto destNode : node->adjacencyList) {
                    cout<<destNode->number<<" ";
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
        int graphSize(){
            return nodeList.size();
        }
    private:
        struct Node {
            Node(int n): number{ n }{}
            Node(int n,vector<Node*> adjList): number{ n },adjacencyList(adjList){}
            ~Node() {}
            bool visited = false;
            int number ;
            vector<Node*> adjacencyList;
        };
        vector<Node*> nodeList;
        queue<Node*> *nodeQueue = nullptr;
        stack<Node*> *nodeStack = nullptr;
        //
        void BFS_backend(){
            if ((int) nodeQueue->size() == 0) return;
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
            if ((int) nodeStack->size() == 0) return;
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
        void resetVisited(){
            for (auto node : nodeList){
                node->visited = false;
            }
        }
};
