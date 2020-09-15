//Main Program to test all Stack methods
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "myStack.hpp"
#include "myQueue.hpp"
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4){
        std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
        return 0;
    }

    //File Intiallization for input and output files
    ifstream inFile;
    ifstream inFile1;
    inFile.open(argv[1]);
    ofstream outfile_stack (argv[2]);
    ofstream outfile_queue (argv[3]);

    //Open input and out file and start with stack & queue methods
    if(inFile.is_open() and outfile_stack.is_open() and outfile_queue.is_open()){
        string str;
        //Stack intialiization with string type object
        myStack <string> stack;
        //Queue intialiization with string type object
        myQueue <string> queue;
        outfile_stack<<"\nitems as they are added to the stack "<<endl;
        outfile_queue<<"\nitems as they are added to the queue "<<endl;
        while(!inFile.eof()){
            inFile >> str;
            /**
            *  @Pre  A new instance has been read from input file
            *  @Post Add the input instance from input file into stack using push
            */
            stack.push(str);
            outfile_stack <<str<<"\n";
            /**
            *  @Pre  A new instance has been read from input file
            *  @Post Add the input instance from input file into queue using push
            */
            queue.enqueue(str);
            outfile_queue <<str<<"\n";
        }
        /**

        *  @Pre  stack as input
        *  @Post Constrcutor with stack object
        */
        myStack <string> stack1 (stack);
        /**

        *  @Pre  stack as input
        *  @Post Constrcutor assigned with stack object
        */
        myStack <string> stack2 =stack;
        /**

        *  @Pre  queue as input
        *  @Post Constrcutor with queue object
        */
        myQueue <string> queue1 (queue);
        /**

        *  @Pre  queue as input
        *  @Post Constrcutor assigned with queue object
        */
        myQueue <string> queue2 = queue;
        /**
        *  @Pre  stack as input
        *  @Post Remove last element of stack until 10 elements are popped
        */
        outfile_stack<<"\nRemove last element of stack until 10 elements are popped "<<endl;
        for (int j=0; j<10;j++){
            outfile_stack <<stack.pop()<<"\n";
        }
        /**
        *  @Pre  queue as input
        *  @Post Remove last element of queue until 10 elements are popped
        */
        outfile_queue<<"\nRemove last element of queue until 10 elements are popped "<<endl;
        for (int j=0; j<10;j++){
            outfile_queue <<queue.dequeue()<<"\n";
        }
        /**
        *  @Pre  stack as input
        *  @Post Print top element of stack
        */
        outfile_stack<<"\ntop element of stack "<<endl;
        outfile_stack <<stack.top()<<"\n";
        /**
        *  @Pre  queue as input
        *  @Post Print front element of queue
        */
        outfile_queue<<"\nfront element of queue "<<endl;
        outfile_queue <<queue.front()<<"\n";
        /**
        *  @Pre  stack as input
        *  @Post Check if stack is empty or not print 0 if empty 1 if not empty
        */
        outfile_stack<<"\n*  @Post Check if stack is empty or not print 0 if empty 1 if not empty "<<endl;
        if(stack.empty()==true){
            outfile_stack <<0<<"\n";
        }
        else{
            outfile_stack << 1<<"\n";
        }
        /**
        *  @Pre  queue as input
        *  @Post Check if queue is empty or not print 0 if empty 1 if not empty
        */
        outfile_queue<<"\nCheck if queue is empty or not print 0 if empty 1 if not empty "<<endl;
        if(queue.empty()==true){
            outfile_queue <<0<<"\n";
        }
        else{
            outfile_queue << 1<<"\n";
        }
        /**
        *  @Pre  The new stack as input
        *  @Post Print all the stack elemetns and empty stack
        */
        outfile_stack<<"\nPrint all the stack elemetns and empty stack "<<endl;
        while (!stack.empty())  {
            outfile_stack <<stack.pop()<<"\n";
        }
        /**
        *  @Pre  The new queue as input
        *  @Post Print all the queue elemetns and empty queue
        */
        outfile_queue<<"\nPrint all the queue elemetns and empty queue "<<endl;
        while (!queue.empty())  {
            outfile_queue <<queue.dequeue()<<"\n";
        }
        /**
        *  @Pre  Input 10 elemenets from input file (this is to verify clear)
        *  @Post add elements to stack and queue
        */
        inFile1.open(argv[1]);
        int count=0;
        string str1;
        while(!inFile1.eof() and (count !=10)){
            inFile1 >> str1;
            stack.push(str);
            queue.enqueue(str1);
            count=count+1;
        }
        inFile1.close();
        /**
        *  @Pre  stack as input
        *  @Post Print top element of stack
        */
        outfile_stack<<"\nPrint top element of stack "<<endl;
        outfile_stack <<stack.top()<<"\n";
        /**
        *  @Pre  queue as input
        *  @Post Print front element of queue
        */
        outfile_queue<<"\n Print front element of queue "<<endl;
        outfile_queue <<queue.front()<<"\n";
        /**
        *  @Pre  The new stack as input
        *  @Post Clear stack
        */
        stack.clear();
        /**
        *  @Pre  The new queue as input
        *  @Post Clear queue
        */
        queue.clear();
        /**
        *  @Pre  stack as input
        *  @Post Check if stack is empty or not print 0 if empty 1 if not empty
        */
        outfile_stack<<"\nCheck if stack is empty or not print 0 if empty 1 if not empty "<<endl;
        if(stack.empty()==true){
            outfile_stack <<0<<"\n";
        }
        else{
            outfile_stack << 1<<"\n";
        }
        /**
        *  @Pre  queue as input
        *  @Post Check if queue is empty or not print 0 if empty 1 if not empty
        */
        outfile_queue<<"\nCheck if queue is empty or not print 0 if empty 1 if not empty "<<endl;
        if(queue.empty()==true){
            outfile_queue <<0<<"\n";
        }
        else{
            outfile_queue << 1<<"\n";
        }
    }
    else{
        cout << "The instance.txt file cannot be opened";
    }
    inFile.close();
    outfile_stack.close();
    outfile_queue.close();
}
