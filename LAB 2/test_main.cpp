//Main Program to test all Doubly Linked list methods
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "myDlList.hpp"
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
//Open input and out file and start with Doubly linked list methods
if(inFile.is_open() and outfile.is_open())

  {
    int num;
  //Doubly linked list(DLL) intialiization
    myDlList<int> dll;
    while(!inFile.eof())
    {
         inFile >> num;
  /**
  *  @Pre  A new instance has been read from input file
  *  @Post Add the input instance from input file into DLL using push back
  */
         dll.push_front(num);
    }
  /**
  *  @Pre  The new DLL as input
  *  @Post Print all the DLL elemetns using iterator
  */
   myDlList<int>::iterator i;
   for (i = dll.begin(); i != dll.end(); ++i)
    {
        outfile << *i << "\n";
    }
  /**

  *  @Pre  DLL as input
  *  @Post Constrcutor with DLL object
  */
   myDlList<int> Dll1 (dll);
  /**
  *  @Pre  DLL as input
  *  @Post Operator overload testing operator=
  */
    myDlList<int> dll2 = myDlList<int>(dll);
  /**
  *  @Pre  The new DLL as input
  *  @Post Print all the DLL elemetns using const iterator
  */
   myDlList<int>::const_iterator c_i;
   for (c_i= dll2.begin(); c_i != dll2.end(); ++c_i)
    {
        outfile << *c_i << "\n";
    }
  /**
  *  @Pre  DLL as input
  *  @Post Operator overload testing operator= with rvalue reference as parameter
  */
    myDlList<int> dll3 = myDlList<int>(myDlList<int>(dll));
  /**
  *  @Pre  The new DLL as input
  *  @Post Print all the DLL elemetns with out using iterators
  */
    for (int& operatorRhsDLLVal : dll3) {
         outfile <<operatorRhsDLLVal<<"\n";
       }
  /**
  *  @Pre  DLL as input
  *  @Post Print DLL size
  */
    outfile << dll.size()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Print first element of DLL
  */
    outfile <<dll.front()<<"\n";
    /**
  *  @Pre  DLL as input
  *  @Post Print last element of DLL
  */
    outfile <<dll.back()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Check if DLL is emoty or not print 0 if empty 1 if not empty
  */
    if(dll.empty()==true)
         {
           outfile <<0<<"\n";
          }
    else
          {
            outfile << 1<<"\n";
          }
  /**
  *  @Pre  DLL as input
  *  @Post Reverse the current DLL
  */

    dll.reverselist();
  /**
  *  @Pre  The new DLL as input
  *  @Post Print all the DLL elemetns with out using iterators : Reversed list
  */
    for (int& reverserlistval : dll) {
         outfile <<reverserlistval<<"\n";
       }

//OPen a new file to get some elements from same instance file
    inFile1.open(argv[1]);
    int count=0;
    num=0;
  /**
  *  @Pre  DLL as input
  *  @Post Add first 1o elements of inout instancefile into DLL using push back method and create a new DLL
  */
    myDlList<int> dll4;
    while(!inFile1.eof() and (count !=10))
    {
         inFile1 >> num;
         dll4.push_back(int(num));
         count=count+1;
    }
    inFile1.close();
    myDlList<int> dll5 = dll.appendList(dll4);
  /**
  *  @Pre  The new DLL as input
  *  @Post Print all the DLL elemetns using iterators
  */
   for (i = dll5.begin(); i != dll5.end(); ++i)
    {
        outfile << *i << "\n";
    }
  /**
  *  @Pre  DLL as input
  *  @Post Print DLL size
  */
    outfile <<dll.size()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Print last element of DLL
  */
    outfile <<dll.back()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Remove last element of DLL using pop back
  */
    dll.pop_back();
  /**
  *  @Pre  DLL as input
  *  @Post Print last element of DLL
  */
    outfile <<dll.back()<<"\n";
    /**
  *  @Pre  DLL as input
  *  @Post Print first  element of DLL
  */
    outfile <<dll.front()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Remove first element of DLL using pop front
  */
    dll.pop_front();
  /**
  *  @Pre  DLL as input
  *  @Post Print first element of DLL
  */
    outfile <<dll.front()<<"\n";
  /**
  *  @Pre  DLL as input
  *  @Post Clears the list
  */
    dll.clear();
    /**
  *  @Pre  DLL as input
  *  @Post Print DLL size :Must be 0
  */
    outfile << dll.size()<<"\n";
  }
else
  {
      cout << "The instance.txt file cannot be opened";
  }
inFile.close();
outfile.close();
}
