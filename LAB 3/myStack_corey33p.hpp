/*
myStack.hpp
Written by Corey Anderson for

EECS 560 Discrete Structures

Lab assignment #3
*/

#include <iostream>
using namespace std;

template <typename ItemType>
class myStack{
    private:
        int stackSize = 0;
        int capacity = 10;
        int headIndex = 0;
        ItemType *stackArray = new ItemType[10];
    public:
        myStack(){}
        myStack( myStack && rhs ):stackSize{rhs.stackSize},capacity{rhs.capacity},headIndex{rhs.headIndex},stackArray{rhs.stackArray}{
            rhs.stackSize = 0;
            rhs.capacity = 10;
            rhs.headIndex = 0;
        }
        myStack & operator= ( myStack && rhs ){
            std::swap(stackSize,rhs.stackSize);
            std::swap(capacity,rhs.capacity);
            std::swap(headIndex,rhs.headIndex);
            ItemType *temp = stackArray;
            stackArray = rhs.stackArray;
            rhs.stackArray = temp;
            return *this;
        }
        myStack(const myStack<ItemType> & rhs){
            stackSize = rhs.stackSize;
            capacity = rhs.capacity;
            headIndex = rhs.headIndex;
            delete [] stackArray;
            stackArray = new ItemType[capacity];
            for (int i=0;i<stackSize;i++){
                stackArray[i] = rhs.stackArray[i];
            }
        }
        myStack & operator= ( const myStack & rhs ){
            myStack copy = rhs;
            std::swap( *this, copy );
            return *this;
        }
        virtual ~myStack(){
            delete [] stackArray;
        }
        void push(const ItemType& newEntry){
            stackSize++;
            if (stackSize > capacity){
                ItemType *newStackArray = new ItemType[2*capacity];
                for (int i=0;i<stackSize;i++){
                    int stackArrayIndex = headIndex + i;
                    if(stackArrayIndex >= capacity){
                        stackArrayIndex = stackArrayIndex % capacity;
                    }
                    newStackArray[i] = stackArray[stackArrayIndex];
                }
                capacity *= 2;
                headIndex = 0;
                delete [] stackArray;
                ItemType *temp = stackArray;
                stackArray = newStackArray;
                newStackArray = temp;
            }
            int newPosition = (headIndex + stackSize - 1) % capacity;
            stackArray[newPosition] = newEntry;
            // printStack();
        }
        ItemType pop(){
            if (!empty()){
                int tailIndex = (headIndex + stackSize - 1) % capacity;
                stackSize--;
                return stackArray[tailIndex];
            }
            return stackArray[headIndex];
        }
        ItemType top() const{
            int tailIndex = (headIndex + stackSize - 1) % capacity;
            return stackArray[tailIndex];
        }
        bool empty() const{
            return (stackSize == 0);
        }
        void clear(){
            while (!empty()){
                pop();
            }
        }
        void printStack(){
            cout<<"-----------printing Stack------------"<<endl;
            cout<<"stackSize: "<<stackSize<<endl;
            cout<<"capacity: "<<capacity<<endl;
            cout<<"headIndex: "<<headIndex<<endl;
            for (int i=0;i<stackSize;i++){
                int newI;
                if(i >= capacity){
                    newI = (headIndex + i) % capacity;
                } else {
                    newI = i;
                }
                cout<<stackArray[newI];
                if ((newI!=stackSize-1)){
                    cout<<",";
                }
                if (i==stackSize-1){
                    cout<<endl;
                }
            }
            cout<<"--------print complete--------"<<endl;
        }
        int getstackSize(){
            return stackSize;
        }
};
