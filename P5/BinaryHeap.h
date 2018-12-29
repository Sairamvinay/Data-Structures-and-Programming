        #ifndef _BINARY_HEAP_H_
        #define _BINARY_HEAP_H_

        #include "dsexceptions.h"
        #include "supplement.h"
        //#include "vector.h"

        // BinaryHeap class
        //
        // CONSTRUCTION: with a negative infinity sentinel and
        //               optional capacity (that defaults to 100)
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted

       // template <class Comparable>
    
        
        class BinaryHeap
        {
          public:
            explicit BinaryHeap( int capacity = 100 );
            bool isEmpty( ) const;
            bool isFull( ) const;
            const int & findMax( ) const;

            void insert(int x );
            void deleteMax( );
            void makeEmpty( );

          private:
            int  currentSize;  // Number of elements in heap
            int* array;        // The heap array
            int Capacity;
            void buildHeap( );
            void percolateDown( int hole );
        };

       // #include "BinaryHeap.cpp"
        #endif
