        #include "QuadraticProbing.h"


       
        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */

        QuadraticHashTable::QuadraticHashTable(int s): size(s){;}

        void QuadraticHashTable::insert( Locs x )
        {
                // Insert x as active
            int currentPos = x.oldLoc % size;
            while (array[currentPos].oldLoc > 1 && array[currentPos].oldLoc != x.oldLoc){
                if (++currentPos == size){
                    currentPos = 0;
                }

            }
            array[currentPos] = x;
        }

        
        


        /**
         * Remove item x from the hash table.
         */
      
        void QuadraticHashTable::remove( Locs x )
        {
            int currentPos = x.oldLoc % size;
            while (array[currentPos].oldLoc > 1 && array[currentPos].oldLoc != x.oldLoc){
                if (++currentPos == size){
                    currentPos = 0;
                }
            }
            if (array[currentPos].oldLoc == x.oldLoc)
                array[currentPos].oldLoc = 1;
        }

        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
       
        Locs& QuadraticHashTable::find( Locs  x ) 
        {
           int currentPos = x.oldLoc % size;
            while (array[currentPos].oldLoc > 1 && array[currentPos].oldLoc != x.oldLoc){
                if (++currentPos == size){
                    currentPos = 0;
                }
            }
            return array[currentPos].oldLoc==x.oldLoc? array[ currentPos ] : ITEM_NOT_FOUND;
        }


