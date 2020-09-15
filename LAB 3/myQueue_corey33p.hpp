/*
myQueue.hpp
Written by Corey Anderson for

EECS 560 Discrete Structures

Lab assignment #3
*/

#include <iostream>
#include <array>
using namespace std;

template <typename ItemType>
class myQueue{
    private:
        int queueSize = 0;
        int capacity = 10;
        int headIndex = 0;
        ItemType *queueArray = new ItemType[10];
    public:
        myQueue(){}
        myQueue( myQueue && rhs ):queueSize{rhs.queueSize},capacity{rhs.capacity},headIndex{rhs.headIndex},queueArray{rhs.queueArray}{
            rhs.queueSize = 0;
            rhs.capacity = 10;
            rhs.headIndex = 0;
        }
        myQueue & operator= ( myQueue && rhs ){
            std::swap(queueSize,rhs.queueSize);
            std::swap(capacity,rhs.capacity);
            std::swap(headIndex,rhs.headIndex);
            ItemType *temp = queueArray;
            queueArray = rhs.queueArray;
            rhs.queueArray = temp;
            return *this;
        }
        myQueue(const myQueue<ItemType> & rhs){
            queueSize = rhs.queueSize;
            capacity = rhs.capacity;
            headIndex = rhs.headIndex;
            delete [] queueArray;
            queueArray = new ItemType[capacity];
            for (int i=0;i<queueSize;i++){
                queueArray[i] = rhs.queueArray[i];
            }
        }
        myQueue & operator= ( const myQueue & rhs ){
            myQueue copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        virtual ~myQueue(){
            delete [] queueArray;
        }
        void enqueue(ItemType& newEntry){
            queueSize++;
            if (queueSize > capacity){
                ItemType *newQueueArray = new ItemType[capacity*2];
                for (int i=0;i<queueSize;i++){
                    int queueArrayIndex = headIndex + i;
                    if(queueArrayIndex >= capacity){
                        queueArrayIndex = queueArrayIndex % capacity;
                    }
                    newQueueArray[i] = queueArray[queueArrayIndex];
                }
                capacity *= 2;
                headIndex = 0;
                delete [] queueArray;
                ItemType *temp = queueArray;
                queueArray = newQueueArray;
                newQueueArray = temp;
            }
            int newPosition = (headIndex + queueSize - 1) % capacity;
            queueArray[newPosition] = newEntry;
            // printQueue();
        }
        ItemType dequeue(){
            int oldHeadIndex = headIndex;
            headIndex++;
            if (headIndex == capacity){
                headIndex = 0;
            }
            queueSize--;
            return queueArray[oldHeadIndex];
        }
        ItemType front() const{
            return queueArray[headIndex];
        }
        bool empty() const{
            return (queueSize == 0);
        }
        void clear(){
            while (!empty()){
                dequeue();
            }
        }
        void printQueue(){
            cout<<"-----------printing Queue------------"<<endl;
            cout<<"queueSize: "<<queueSize<<endl;
            cout<<"capacity: "<<capacity<<endl;
            cout<<"headIndex: "<<headIndex<<endl;
            for (int i=0;i<queueSize;i++){
                int newI;
                if(i >= capacity){
                    newI = (headIndex + i) % capacity;
                } else {
                    newI = i;
                }
                cout<<queueArray[newI];
                if ((newI!=queueSize-1)){
                    cout<<",";
                }
                if (i==queueSize-1){
                    cout<<endl;
                }
            }
            cout<<"--------print complete--------"<<endl;
        }
};
