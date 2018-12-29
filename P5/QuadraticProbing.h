        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        //#include "vector.h"
        //#include "mystring.h"

       
   
        #include "supplement.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings
        
        //adt for the cities -> HT stored on basis of ID
            //i need an adjacency list
        
        
        class QuadraticHashTable
        {
          public:
            HashEntry* cities;
            int numCities;
            int numRoads;
            explicit QuadraticHashTable(City* array, int numR, int numC );
            int findPos( const int & x ) const;
            void insert( const City & x );
            //City* find( const int & ID) ;
            void remove( const int & x );
            City2* find( const int & x );
            void makeEmpty( );
            //void insert( const City & x );
            //void remove( const int& id );

            
          private:

            bool isActive( int currentPos ) const;
            int currentSize ;
            //int findPos( const int & id ) const;
            int hash( int id, int tableSize ) const;
            
        };

        //#include "QuadraticProbing.cpp"
        #endif
