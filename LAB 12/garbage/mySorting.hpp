#include <vector>
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

/**
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right,bool reverse ){
    if (reverse == false){
        int center = ( left + right ) / 2;
        if( a[ center ] < a[ left ] )
            std::swap( a[ left ], a[ center ] );
        if( a[ right ] < a[ left ] )
            std::swap( a[ left ], a[ right ] );
        if( a[ right ] < a[ center ] )
            std::swap( a[ center ], a[ right ] );
        if (!(a[ left ] <= a[ center ]) && (a[ center ] <= a[ right ])){
            if (!((left < center) && (center < right))){
                cerr<<"left: "<<left<<endl;
                cerr<<"right: "<<right<<endl;
                cerr<<"center: "<<center<<endl;
                cerr<<"a[ left ]: "<<a[ left ]<<endl;
                cerr<<"a[ right ]: "<<a[ right ]<<endl;
                cerr<<"a[ center ]: "<<a[ center ]<<endl;
                assert((1==0));
            }
        }
        // Place pivot at position right - 1
        std::swap( a[ center ], a[ right - 1 ] );
        return a[ right - 1 ];
    } else {
        int center = ( left + right ) / 2;
        
        if( a[ center ] > a[ left ] )
            std::swap( a[ left ], a[ center ] );
        if( a[ right ] > a[ left ] )
            std::swap( a[ left ], a[ right ] );
        if( a[ right ] > a[ center ] )
            std::swap( a[ center ], a[ right ] );
        if (!(a[ left ] >= a[ center ]) && (a[ center ] >= a[ right ])){
            if (!((left < center) && (center < right))){
                cerr<<"left: "<<left<<endl;
                cerr<<"right: "<<right<<endl;
                cerr<<"center: "<<center<<endl;
                cerr<<"a[ left ]: "<<a[ left ]<<endl;
                cerr<<"a[ right ]: "<<a[ right ]<<endl;
                cerr<<"a[ center ]: "<<a[ center ]<<endl;
                assert((1==0));
            }
        }
        // Place pivot at position right - 1
        std::swap( a[ center ], a[ right - 1 ] );
        return a[ right - 1 ];
    }
}


template <typename Comparable>
void printList( vector<Comparable> a ,std::string message,int pivot = -1, int l = -1, int r = -1){
    int buffer = 30;
    std::string line = message;
    for (int i = 0;i<buffer - (int) message.length();i++)
        line = line + " ";
    int i = 0;
    int pPos,lPos,rPos;
    for (auto thing : a){
        line = line + " " + to_string(thing);
        if (i == pivot){
            pPos = line.length()-1;
        } else if (i == l){
            lPos = line.length()-1;
        } else if (i == r) {
            rPos = line.length()-1;
        }
        i++;
    }
    line+="\n";
    int len = line.length();
    for ( int i = 0;i< len;i++){
        if (i == pPos){
            line+="^";
        } else if ((i==lPos)&&(i==rPos)){
            line+="X";
        } else if (i == lPos){
            line+="L";
        } else if (i == rPos) {
            line+="R";
        } else {
            line += " ";
        }
    }
    cerr<<line<<endl;
    assert(lPos!=rPos);
}


void printList( vector<int>& a ,std::string message,int pivot = -1, int l = -1, int r = -1){
    int buffer = 30;
    std::string line = message;
    for (int i = 0;i<buffer - (int) message.length();i++)
        line = line + " ";
    int i = 0;
    int pPos,lPos,rPos;
    for (auto thing : a){
        line = line + " " + to_string(thing);
        if (i == pivot){
            pPos = line.length()-1;
        } else if (i == l){
            lPos = line.length()-1;
        } else if (i == r) {
            rPos = line.length()-1;
        }
        i++;
    }
    line+="\n";
    int len = line.length();
    for ( int i = 0;i< len;i++){
        if (i == pPos){
            line+="^";
        } else if ((i==lPos)&&(i==rPos)){
            line+="X";
        } else if (i == lPos){
            line+="L";
        } else if (i == rPos) {
            line+="R";
        } else {
            line += " ";
        }
    }
    cerr<<line<<endl;
    assert(lPos!=rPos);
}

/**
* Simple insertion sort.
*/
template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right, bool reverse ){
    if (reverse == false){
        for( int p = left; p < right+1; ++p ){
            Comparable tmp = std::move( a[ p ] );
            int j;
            for( j = p; j > 0 && tmp < a[ j - 1 ]; --j )
                a[ j ] = std::move( a[ j - 1 ] );
            a[ j ] = std::move( tmp );
        }
        // for (int i = left + 1;i<right;i++){
            // printList(a,"blah",-1,int(left),int(right));
        //     cerr<<"i: "<<i<<endl;
        //     while (a[i-1]<a[i]){
        //         i++;
        //     }
        //     cerr<<"i: "<<i<<endl;
        //     int j = i-1;
        //     cerr<<"j: "<<j<<endl;
        //     while (j > left && a[j]<a[j+1]){
        //         j--;
        //     }
        //     cerr<<"j: "<<j<<endl;
        //     std::swap(a[i],a[j]);
        //     printList(a,"blah",-1,int(j),int(i));
        // }
        // printList(a,"blah",-1,int(left),int(right));
        //
        bool badSort = false;
        for (int i = left+1;i < right;i++)
            if (a[i-1] > a[i])
                badSort = true;
        if (badSort){
            cerr<<"bad sortA.";
            for (int i = left;i < right;i++)
                cerr<<" "<<a[i];
            cerr<<endl;
        }
    } else {
        for( int p = left; p < right+1; ++p ){
            Comparable tmp = std::move( a[ p ] );
            int j;
            for( j = p; j > 0 && tmp > a[ j - 1 ]; --j )
                a[ j ] = std::move( a[ j - 1 ] );
            a[ j ] = std::move( tmp );
        }
        //
        bool badSort = false;
        for (int i = left+1;i < right;i++)
            if (a[i-1] < a[i])
                badSort = true;
        if (badSort){
            cerr<<"bad sortB.";
            for (int i = left;i < right;i++)
                cerr<<" "<<a[i];
            cerr<<endl;
        }
    }
}

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right, bool reverse ){
    // printList(a,"starting ",-1,left,right);
    if (reverse == false){
        if( left + 10 <= right ){
        // if (1) {
            const Comparable & pivot = median3( a, left, right, reverse );
            // printList(a,"pivot set ",right-1,left,right-2);
            // cerr<<"pivot: "<<pivot<<endl;

            // Begin partitioning
            int i = left+1, j = right - 2;
            // int check = 0;
            while (true){
                while( a[ i ] < pivot ) {
                    i++;
                    // printList(a,"left moved right ",right,i,j);
                }
                while( pivot < a[ j ] ) {
                    j--;
                    // printList(a,"right moved left ",right,i,j);
                }
                if( i < j ){
                    std::swap( a[ i ], a[ j ] );
                    // printList(a,"swapped "+to_string(a[i])+" and "+to_string(a[j]),right,i,j);
                } else
                    break;
                // check++;
                // assert(check<=(int) a.size());
            }
            std::swap( a[ i ], a[ right - 1 ] ); // Restore pivot
            // cout<<a[ i ]<<endl;
            //
            // string message = "pivot "+to_string(a[i])+" sorted. ";
            // printList(a,message,i);
            // bool badPivot = false;
            // if ((a[left]>a[i])||(a[i]>a[right-1])||(a[left]>a[right-1]))
            //     badPivot = true;
            // if (badPivot){
            //     cerr<<"bad pivot "+to_string(a[i])+".\n";
            //     cerr<<"a[left]: "<<a[left]<<endl;
            //     cerr<<"a[i]: "<<a[i]<<endl;
            //     cerr<<"a[right-1]: "<<a[right-1]<<endl;
            // }

            quicksort( a, left, i - 1, reverse );// Sort small elements
            // printList(a,"insertionSort. ",-1,left,i-1);
            quicksort( a, i + 1, right, reverse );// Sort large elements
            // printList(a,"insertionSort. ",-1,i + 1,right);
        } else { // Do an insertion sort on the subarray
            insertionSort( a, left, right, reverse );
        }
    } else {
        if( left + 10 <= right ){
            const Comparable & pivot = median3( a, left, right, reverse );

            // Begin partitioning
            int i = left, j = right - 1;
            for( ; ; ){
                while( a[ ++i ] > pivot ) { }
                while( pivot > a[ --j ] ) { }
                if( i < j )
                    std::swap( a[ i ], a[ j ] );
                else
                    break;
            }
            std::swap( a[ i ], a[ right - 1 ] ); // Restore pivot
            cout<<a[ i ]<<endl;
            //
            bool badPivot = false;
            if ((a[left]<a[i])||(a[i]<a[right-1])||(a[left]<a[right-1]))
                badPivot = true;
            if (badPivot){
                cerr<<"bad pivot.";
                cerr<<"a[left]: "<<a[left]<<endl;
                cerr<<"a[i]: "<<a[i]<<endl;
                cerr<<"a[right-1]: "<<a[right-1]<<endl;
            }

            quicksort( a, left, i - 1, reverse );// Sort small elements
            quicksort( a, i + 1, right, reverse );// Sort large elements
        } else { // Do an insertion sort on the subarray
            insertionSort( a, left, right, reverse );
        }
    }
}

/**
* Quicksort algorithm (driver).
*/
template <typename Comparable>
void quickSort( vector<Comparable> & a, bool reverse = false){
    quicksort( a, 0, a.size( ) - 1,reverse );
}