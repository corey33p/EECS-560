//Main Program to test Binary Search Tree functions
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "myBinarySearchTree.hpp"
using namespace std;
int main(int argc, char* argv[])
{
if(argc != 3)
    {
        std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
        return 0;
    }

//File Intiallization for input and output files
ifstream inFile;
ifstream inFile1;
inFile.open(argv[1]);
ofstream outfile (argv[2]);

//Open input and out file and sstart with hash table methods
if(inFile.is_open() and outfile.is_open())

  {
    int num;
//Binary search tree object with <int> as templete type
    myBinarySearchTree<int> BST;
    while(!inFile.eof())
    {
         inFile >> num;
/**
*  @Pre  A new instance has been read from input file
*  @Post Add the input instance from input file into BST using insert
*/
         BST.insert(num);
    }
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in InOrder to output file
*/
   BST.printTreeInorder(outfile);
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints minimum element of BST to output file
*/
   outfile <<BST.findMin() <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints maximum element of BST to output file
*/
   outfile<<BST.findMax() <<"\n";
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in PostOrder to output file
*/
   BST.printTreePostorder(outfile);
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in PreOrder to output file
*/
   BST.printTreePreorder(outfile);
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Check if BST is empty or not
*/
   outfile <<BST.isEmpty( )<<"\n";
   outfile <<"\n";

//OPen a new file to get some elements from same instance file
  /**
  *  @Pre  Current BST as input
  *  @Post check if first 10 elements from input files are present in BST
  */
  inFile1.open(argv[1]);
  int count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {
         inFile1 >> num;
         if(BST.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
  inFile1.close();
  /**
  *  @Pre  Current BST as input
  *  @Post Remove first 10 elements from input files from BST
  */
  inFile1.open(argv[1]);
  count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {
         inFile1 >> num;
         BST.remove(num);
         count=count+1;
    }
    inFile1.close();
  /**
  *  @Pre  Current BST as input
  *  @Post check if first 10 elements from input files are present in BST
  */
  inFile1.open(argv[1]);
  count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {
         inFile1 >> num;
         if(BST.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
    inFile1.close();
  }
else
  {
      cout << "The instance.txt file cannot be opened";
  }
inFile.close();
outfile.close();
}
