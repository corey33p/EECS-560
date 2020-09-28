//Main Program to test Infix Posifx calcualtion of stack
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "myInfixPostfix.hpp"
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
inFile.open(argv[1]);
ofstream outfile (argv[2]);
//Open input and out file and start with stack & queue methods
if(inFile.is_open() and outfile.is_open())

  {
    string str;
  //Stack intialiization with string type object
    while(std::getline(inFile, str))
    {
  //create and object of Infix Postfix class
         myInfixPostfix infixpostfix;
  /**
  *  @Pre  A new instance string has been read from input file
  *  @Post get the postfix result by passing string of infix expression

  */
         string postfix_exp = infixpostfix.getPostfix(str);
  /**
  *  @Pre  Postfix expression as input
  *  @Post get the postfix calculated result by passing postfix expression
  */
         outfile<< postfix_exp << "   :   "<< infixpostfix.PostfixCalculator(postfix_exp)<<"\n";

    }
  }
else
  {
      cout << "The instance.txt file cannot be opened";
  }
inFile.close();
outfile.close();

}
