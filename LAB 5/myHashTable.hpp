/*
myHashTable.hpp

Code copied and modified from ("Data Structures And Algorithm Analysis in C++"
by Mark Allen Weiss) by Corey Anderson

Code was copied from Figures 5.6 through 5.10 on pages 197 through 200

EECS 560 Discrete Structures
Lab assignment #5
*/

#include <math.h>
#include <vector>
#include "myDlList.hpp"

template <typename hashitem>
class myHashTable {
    public:
        explicit myHashTable( int size = 101 ){
            currentSize = size;
            for (int i = 0;i < currentSize;i++){
                theLists.push_back(myDlList<hashitem>());
            }
        }
        virtual ~myHashTable(){
            // cout<<"theLists.size(): "<<theLists.size()<<endl;
            // cout<<"currentSize: "<<currentSize<<endl;
            // cout<<"hashsize(): "<<hashsize()<<endl;
        }
        bool contains( const hashitem & x ) const{
            auto & whichList = theLists[ myhash( x ) ];
            bool found = whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end();
            return found;
        }
        void makeEmpty(){
            for( auto & thisList : theLists )
            thisList.clear( );
        }
        bool insert( const hashitem & x ){
            // cout<<"theLists.size(): "<<theLists.size()<<endl;
            auto & whichList = theLists[ myhash( x ) ];
            bool found = whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end();
            if(found)
                return false;
            whichList.push_back( x );
            if( ++currentSize > (int) theLists.size( ) )
                rehash( );
            return true;
        }
        bool insert( hashitem && x ){
            auto & whichList = theLists[ myhash( x ) ];
            bool found = whichList.find( whichList.begin(), whichList.end(), x ) != whichList.end();
            if(found)
                return false;
            whichList.push_back( x );
            if( ++currentSize > (int) theLists.size( ) )
                rehash( );
            return true;
        }
        bool remove( const hashitem & x ){
            auto & whichList = theLists[ myhash( x ) ];
            auto itr = whichList.find( whichList.begin(), whichList.end(), x );
            bool found = (itr != end( whichList ));
            if(!found)
                return false;
            whichList.erase( itr );
            --currentSize;
            return true;
        }
        typename myDlList<hashitem> ::iterator getiteratorbegin(int index){
            auto & whichList = theLists[ index ];
            return begin(whichList);
        }
        typename myDlList<hashitem> ::iterator getiteratorend(int index){
            auto & whichList = theLists[ index ];
            return end(whichList);
        }
        int hashsize(){
            return theLists.size();
        }
    private:
        vector<myDlList<hashitem>> theLists; // The array of Lists
        int currentSize = 101;

        void rehash( ){
            vector<myDlList<hashitem>> oldLists = theLists;

            // Create new double(ish)-sized, empty table
            theLists.resize( nextPrime( 2 * theLists.size( ) ) );
            for( auto & thisList : theLists )
                thisList.clear( );

            // Copy table over
            currentSize = 0;
            for( auto & thisList : oldLists )
                for( auto & x : thisList )
                    insert( std::move( x ) );
        }
        int nextPrime(int n){
            bool isPrime = false;

            // lambda function to check if m is prime
            auto checkPrime = [&](int m){
                isPrime = true;
                if (m<2) isPrime = false;
                else {
                    for (int i = 2;i <= pow(m,.5);i++){
                        if (m%i == 0){
                            isPrime = false;
                            break;
                        }
                    }
                }
            };

            // iterate n until it is prime
            while (!isPrime){
                 n++;
                 checkPrime(n);
             }
            return n;
        }
        size_t myhash( const hashitem & x ) const{
            static hash<hashitem> hf;
            size_t result = hf( x ) % theLists.size( );
            return result;
        }
        void printHashTable(){
            int index = 0;
            for (auto list : theLists){
                cout<<"\nindex: "<<index<<endl;
                list.print_list();
                index++;
            }
        }
};
