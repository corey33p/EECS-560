#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

template <typename Comparable>
class myBinaryMinHeap {
    public:
        explicit myBinaryMinHeap( int capacity = 100 ){
            arrayCapacity = capacity;
            currentSize = 0;
            array.reserve(capacity);
        }
        explicit myBinaryMinHeap( const vector<Comparable> & items )
            : array( items.size( ) + 10 ), currentSize{ items.size( ) }{
            for( int i = 0; i < items.size( ); ++i )
                array[ i + 1 ] = items[ i ];
            buildHeap( );
        }

        bool isEmpty( ) const{
            return (currentSize == 0);
        }
        const Comparable & findMin( ) const{
            if( isEmpty( ) )
                std::cerr << "Error: findMin called while heap is empty"<<endl;

            return array[1];
        }

        /**
        * Insert item x, allowing duplicates.
        */
        void insert( const Comparable & x ){
            if( (unsigned int) currentSize == array.capacity() - 1 ){
                int newArrayCapacity = arrayCapacity * 2;
                Comparable new_array[newArrayCapacity];
                for (int i = 0;i<arrayCapacity;i++){
                    new_array[i] = array[i];
                }
                array = vector<Comparable>(newArrayCapacity);
                array.reserve(newArrayCapacity);
                for (int i = 0;i<arrayCapacity;i++){
                    array[i] = new_array[i];
                }
                arrayCapacity = newArrayCapacity;
            }

            // Percolate up
            int hole = ++currentSize;
            Comparable copy = x;
            array[ 0 ] = std::move( copy );
            for( ; x < array[ hole / 2 ]; hole /= 2 )
                array[ hole ] = std::move( array[ hole / 2 ] );
            array[ hole ] = std::move( array[ 0 ] ); // swap last and first elements
            // print(1);
        }
        // void insert( const Comparable & x ){
        //     int hole = currentSize;
        //     array.push_back(x);
        //     // cout<<"\n---------------\nhole: "<<hole<<endl;
        //     // cout<<"x: "<<x<<endl;
        //     // cout<<"array[hole]: "<<array[hole]<<endl;
        //     // cout<<"array[hole / 2]: "<<array[hole / 2]<<endl;
        //     while (array[hole / 2] > array[hole]){
        //         std::swap(array[hole / 2],array[hole]);
        //         hole /= 2;
        //     }
        //     currentSize++;
        //     print();
        // }
        void insert( Comparable && x ){
            if( currentSize == array.size( ) - 1 )
                array.resize( array.size( ) * 2 );

            // Percolate up
            int hole = ++currentSize;
            Comparable copy = x;

            array[ 0 ] = std::move( copy );
            for( ; x < array[ hole / 2 ]; hole /= 2 ){
                array[ hole ] = std::move( array[ hole / 2 ] );
            }
            array[ hole ] = std::move( array[ 0 ] );
        }

        /**
        * Remove the minimum item.
        * Reports error message if empty
        */
        void deleteMin( ){
            if( isEmpty( ) )
                std::cerr << "Error: deleteMin( ) called while heap is empty"<<endl;

            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );
        }

        /**
        * Remove the minimum item and place it in minItem.
        * Reports error message if empty
        */
        void deleteMin( Comparable & minItem ){
            if( isEmpty( ) )
                std::cerr << "Error: deleteMin( Comparable & minItem ) called while heap is empty"<<endl;

            minItem = std::move( array[ 1 ] );
            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );
        }
        void makeEmpty( ){
            while( !isEmpty( ) )
                deleteMin();
        }
        void levelOrder(std::ostream & out){
            int itemCount = 1;
            while (itemCount <= currentSize){
                out << array[itemCount] << endl;
                itemCount++;
            }
        }

        void print(int start_at = 0){
            cout<<"\n-------------------------\n";
            cout<<"array: ";
            for (int i = 0;i<currentSize;i++) {
                cout<<array[i]<<",";
            }cout<<endl;
            if (start_at >= currentSize){return;}
            vector<Comparable> new_array;
            for (int i = start_at;i<currentSize;i++){
                new_array.push_back(array[i]);
            }
            if (isEmpty()){ return; }

            int height = 1+(log(currentSize-start_at)/log(2));
            int maxVal = new_array[0];
            int counter = 0;
            for (int i = 0;i<currentSize-start_at;i++) {
                if (new_array[i] > maxVal){
                    maxVal = new_array[i];
                }
                counter ++;
            }
            std::string max = std::to_string(maxVal);
            int spacing = max.length()+1;
            if (spacing % 2 == 1){ spacing++; }
            std::string the_str = "";
            int space_locations_len = spacing*pow(2,height-2)-2;
            int space_locations[space_locations_len];
            for (int i=0; i<space_locations_len; i++) {
                space_locations[i]=0;
            }
            int i = 0;
            for (int j=pow(2,height-1)-1; j<pow(2,height)-1; j++) {
                space_locations[j]=i*spacing;
                i++;
            }

            for (int row=height-1; row>-1; row--){
                cout<<endl;
                std::string row_str = "";
                int line_location = 0;
                for (int entry = pow(2,row)-1;entry<pow(2,row+1)-1;entry++){
                    if (entry < currentSize-start_at) {
                        Comparable value = new_array[entry];
                        int len_entry = std::to_string(value).length();
                        if (row == (height-1)){
                            for (int i = 0; i < (spacing - len_entry);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            row_str = row_str + std::to_string(value);
                            line_location=line_location + len_entry;
                        } else {
                            int child_1_pos = space_locations[entry*2+1];
                            int child_2_pos = space_locations[entry*2+2];
                            int new_pos = (child_1_pos + child_2_pos) / 2;
                            space_locations[entry] = new_pos;
                            int line_location_static = line_location;
                            for (int i = 0;i<(new_pos - line_location_static);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            for (int i = 0; i < (spacing - len_entry);i++){
                                row_str = row_str + " ";
                                line_location++;
                            }
                            row_str = row_str + std::to_string(value);
                            line_location+=len_entry;
                        }
                    }
                }
                row_str = row_str + "\n";
                the_str = row_str + the_str;
            }
            cout<<the_str;
        }

    private:
        int arrayCapacity;
        int currentSize; // Number of elements in heap
        vector<Comparable> array; // The heap array

        /**
        * Establish heap order property from an arbitrary
        * arrangement of items. Runs in linear time.
        */
        void buildHeap( ){
            for( int i = currentSize / 2; i > 0; --i )
                percolateDown( i );
        }

        /**
        * Internal method to percolate down in the heap.
        * hole is the index at which the percolate begins.
        */
        void percolateDown( int hole ){
            int child;
            Comparable tmp = std::move( array[ hole ] );

            for( ; hole * 2 <= currentSize; hole = child ){
                child = hole * 2;
                if( child != currentSize && array[ child + 1 ] < array[ child ] )
                    ++child;
                if( array[ child ] < tmp )
                    array[ hole ] = std::move( array[ child ] );
                else
                    break;
            }
            array[ hole ] = std::move( tmp );
        }
};
