        #include "QuadraticProbing.h"

        /**
         * Construct the hash table.
         */

        QuadraticHashTable::QuadraticHashTable(City* array, int numR, int numC ): numRoads(numR),numCities(numC)
        {
           
           // numCities = numC;
            cities = new HashEntry[numC * 2];

            makeEmpty( );

            //cout << "array[1].ID: " << array[1].ID << endl;

            for (int i=0;i<numC;i++){
                cout << "array[i]: " << array[i].ID << endl;
                insert(array[i]);
            }
            cout << "12 QH" << endl;
        }

        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */

        void QuadraticHashTable::insert( const City & x )
        {
            cout << "QH insert" << endl;
                // Insert x as active
            int currentPos = findPos( x.ID );
            cout << "32: " << currentPos << endl;
            if( isActive( currentPos ) )
                return;
            cout << "35" << endl;
            HashEntry obj(x,0);
            cities[ currentPos ] = obj;
            cout << "37" << endl;
            currentSize+= 1;
        }

        

        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
      
        int QuadraticHashTable::findPos( const int & x ) const
        {
/* 1*/      int collisionNum = 0;
/* 2*/      int currentPos = hash( x, numCities);

/* 3*/      while( cities[ currentPos ].status != 1 &&
                   cities[ currentPos ].myCity.C.ID != x )
            {
                 collisionNum++;
/* 4*/          currentPos = currentPos + (collisionNum*collisionNum);  // Compute ith probe

/* 5*/          if( currentPos >= (numCities*2) )
/* 6*/              currentPos -= (numCities*2);
            }

/* 7*/      return currentPos;
        }


        /**
         * Remove item x from the hash table.
         */
        
        void QuadraticHashTable::remove( const int & x )
        {
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                cities[ currentPos ].status = 2;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
       
        City2* QuadraticHashTable::find( const int & x )
        {
            int currentPos = findPos( x );
            return isActive( currentPos ) ? &(cities[ currentPos ].myCity) : 0;
        }

        /**
         * Make the hash table logically empty.
         */

        void QuadraticHashTable::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < numCities; i++ )
                cities[ i ].status = 1;
        }


        /**
         * Return true if currentPos exists and is active.
         */
        
        bool QuadraticHashTable::isActive( int currentPos ) const
        {
            return cities[ currentPos ].status == 0;
        }
        
        /**
         * A hash routine for ints.
         */

        int QuadraticHashTable::hash( int id, int tableSize ) const
        {
            
            return id % tableSize;
        }
