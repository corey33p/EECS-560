//Main Program to test all vector methods
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "myOwnVector.hpp"
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
        return 0;
    }

    //File Intiallization for input and output files
    ifstream inFile;
    ifstream inFile1;
    inFile.open(argv[1]);
    ofstream outfile (argv[2]);

    //Open input and out file and start with vector methods
    if(inFile.is_open() and outfile.is_open()){
        int num;
        //Vector intialiization
        myOwnVector<int> v;
        while(!inFile.eof()){
            inFile >> num;
            /**
            *  @Pre  A new instance has been read from input file
            *  @Post Add the input instance from input file into vector using push back
            */
            v.push_back(num);
        }
        /**
        *  @Pre  The new vector as input
        *  @Post Print all the vector elemetns using iterator
        */
        myOwnVector<int>::iterator i;
        for (i = v.begin(); i != v.end(); ++i){
            outfile << *i << "\n";
        }
        /**

        *  @Pre  Vector as input
        *  @Post Constrcutor with std vector as object
        */
        myOwnVector<int> stdVec (std::vector<int> v);
        /**
        *  @Pre  Vector as input
        *  @Post Operator overload testing operator=
        */
        myOwnVector<int> v1 = myOwnVector<int>(v);
        /**
        *  @Pre  The new vector as input
        *  @Post Print all the vector elemetns using const iterator
        */
        myOwnVector<int>::const_iterator c_i;
        for (c_i= v1.begin(); c_i != v1.end(); ++c_i){
            outfile << *c_i << "\n";
        }
        /**
        *  @Pre  Vector as input
        *  @Post Operator overload testing operator= with rvalue reference as parameter
        */
        myOwnVector<int> v2 = myOwnVector<int>(myOwnVector<int>(v));
        /**
        *  @Pre  The new vector as input
        *  @Post Print all the vector elemetns with out using iterators
        */
        for (int& operatorRhsVectorVal : v2) {
            outfile <<operatorRhsVectorVal<<"\n";
        }
        /**
        *  @Pre  Vector as input
        *  @Post Print vector size
        */
        outfile << v.size()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Print last element of vector
        */
        outfile <<v.back()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Check if vectoris emoty or not print 0 if empty 1 if not empty
        */
        if(v.empty()==true){
            outfile <<0<<"\n";
        } else {
            outfile << 1<<"\n";
        }
        /**
        *  @Pre  Vector as input
        *  @Post Print vector size
        */
        outfile << v.size()<<"\n";
        inFile1.open(argv[1]);
        myOwnVector<int> v3;
        int count=0;
        num=0;
        /**
        *  @Pre  Vector as input
        *  @Post Add first 1o elements of inout instancefile into vector using push back method and create a new vector
        */
        while(!inFile1.eof() and (count !=10)) {
            inFile1 >> num;
            v3.push_back(int(num));
            count=count+1;
        }
        inFile1.close();
        /**
        *  @Pre  Vector as input
        *  @Post Append the new vector to the exisiting vector
        */
        myOwnVector<int> v4 = v.append(v3);
        /**
        *  @Pre  The new vector as input
        *  @Post Print all the vector elemetns using iterators
        */
        for (i = v.begin(); i != v.end(); ++i) {
            outfile << *i << "\n";
        }
        /**
        *  @Pre  Vector as input
        *  @Post Print vector size
        */
        outfile <<v.size()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Print last element of vector
        */
        outfile <<v.back()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Remove last element of vector using pop back
        */
        v.pop_back();
        /**
        *  @Pre  Vector as input
        *  @Post Print last element of vector
        */
        outfile <<v.back()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Print the capapcity of vector
        */
        outfile << v.capacity()<<"\n";
        /**
        *  @Pre  Vector as input
        *  @Post Resize the vector
        */
        int newVectorSize= v.capacity()+1;
        v.resize(newVectorSize);
        /**
        *  @Pre  Vector as input
        *  @Post Print vector size
        */
        outfile <<v.size()<<"\n";
    } else {
        cout << "The instance.txt file cannot be opened";
    }
    inFile.close();
    outfile.close();
}
