#include <vector>
#include <iostream>
using namespace std;

class myDisjointSet{
    public:
        /**
        * Construct the disjoint sets object.
        * numElements is the initial number of disjoint sets.
        */
        explicit myDisjointSet( int numElements ): s{ vector<int>(numElements, - 1) } { }
        int find( int x ) const{
            if( s[ x ] < 0 )
                return x;
            else
                return find( s[ x ] );
        }

        /**
        * Perform a find.
        * Error checks omitted again for simplicity.
        * Return the set containing x.
        */
        int find( int x ){
            if( s[ x ] < 0 )
                return x;
            else
                return s[ x ] = find( s[ x ] );
        }

        /**
        * Union two disjoint sets.
        * root1 is the root of set 1.
        * root2 is the root of set 2.
        */
        void unionSets( int root1, int root2 ){
            if (root1 == root2) return;
            if (s[ root1 ] <= s[ root2 ]){
                s[ root1 ] = s[ root1 ] + s[ root2 ];
                s[ root2 ] = root1;
            } else {
                s[ root2 ] = s[ root2 ] + s[ root1 ];
                s[ root1 ] = root2;
            }
        }

        void print( int i ){
            cout<<i<<endl;
            if( s[ i ] >= 0 )
                print( s[ i ] );
        }

        int getNumberElements() const{
            return s.size();
        }

        int getSetSize( int i ) const {
            if( s[ i ] < 0 )
                return -s[i];
            else
                return getSetSize( s[ i ] );
        }

        void printVec(){
            cerr<<"--------\nprintVec"<<endl;
            cerr<<"vec size: "<<s.size()<<endl;
            for (auto thing : s)
                cerr<<thing<<",";
            cerr<<"\n--------"<<endl;
        }
    private:
        vector<int> s;
};
