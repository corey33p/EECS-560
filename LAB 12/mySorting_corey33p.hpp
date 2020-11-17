#include <vector>
#include <iostream>
using namespace std;

/**
* Simple insertion sort.
*/
template <typename Comparable>
void insertionSort( vector<Comparable> & a ,int left, int right, bool reverse){
    if (!reverse){
        for( int p = left; p < right+1; ++p ){
            Comparable tmp = std::move( a[ p ] );
            int j;
            for( j = p; j > 0 && tmp < a[ j - 1 ]; --j )
                a[ j ] = std::move( a[ j - 1 ] );
            a[ j ] = std::move( tmp );
        }
    } else {
        for( int p = left; p < right+1; ++p ){
            Comparable tmp = std::move( a[ p ] );
            int j;
            for( j = p; j > 0 && tmp > a[ j - 1 ]; --j )
                a[ j ] = std::move( a[ j - 1 ] );
            a[ j ] = std::move( tmp );
        }
    }
}

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

        // Place pivot at position right - 1
        std::swap( a[ center ], a[ right - 1 ] );
        return a[ right - 1 ];
    }else{
        int center = ( left + right ) / 2;

        if( a[ center ] > a[ left ] )
            std::swap( a[ left ], a[ center ] );
        if( a[ right ] > a[ left ] )
            std::swap( a[ left ], a[ right ] );
        if( a[ right ] > a[ center ] )
            std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
        std::swap( a[ center ], a[ right - 1 ] );
        return a[ right - 1 ];
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
void quicksort( vector<Comparable> & a, int left, int right, bool reverse = false ){
    if (!reverse){
        if( left + 10 <= right ){
            const Comparable & pivot = median3( a, left, right,reverse );

            // Begin partitioning
            int i = left, j = right - 1;
            for( ; ; ){
                while( a[ ++i ] < pivot ) { }
                while( pivot < a[ --j ] ) { }
                if( i < j )
                    std::swap( a[ i ], a[ j ] );
                else
                    break;
            }
            std::swap( a[ i ], a[ right - 1 ] );// Restore pivot
            cout<<a[i]<<endl;
            quicksort( a, left, i - 1,reverse );// Sort small elements
            quicksort( a, i + 1, right,reverse );// Sort large elements
        }
        else {
            // Do an insertion sort on the subarray
            insertionSort( a, left, right,reverse );
        }
    } else {
        if( left + 10 <= right ){
            const Comparable & pivot = median3( a, left, right,reverse );

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
            std::swap( a[ i ], a[ right - 1 ] );// Restore pivot
            cout<<a[i]<<endl;
            quicksort( a, left, i - 1,reverse );// Sort small elements
            quicksort( a, i + 1, right,reverse );// Sort large elements
        }
        else {
            // Do an insertion sort on the subarray
            insertionSort( a, left, right,reverse );
        }
    }
}

/**
* Quicksort algorithm (driver).
*/
template <typename Comparable>
void quickSort( vector<Comparable> & a, bool reverse = false ){
    quicksort( a, 0, a.size( ) - 1,reverse );
}

