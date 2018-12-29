        #ifndef _QUEUEAR_H
        #define _QUEUEAR_H

        #include "dsexceptions.h"
    
    

        // Queue class -- array implementation
        //
        // CONSTRUCTION: with or without a capacity; default is 10
        //
        // ******************PUBLIC OPERATIONS*********************
        // void enqueue( x )      --> Insert x
        // void dequeue( )        --> Return and remove least recently inserted item
        // Object getFront( )     --> Return least recently inserted item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Overflow and Underflow thrown as needed

        class Queue
        {
          public:
            explicit Queue( int capacity = 10 );

            bool isEmpty( ) const;

            bool isFull( ) const;
            int getFront( ) ;

            void makeEmpty( );
            int dequeue( );
            void enqueue( int  x );

          private:
            int* theArray;
            int currentSize;
            int Capacity;
            int front;
            int back;

            void increment( int & x );
        };


        #endif
