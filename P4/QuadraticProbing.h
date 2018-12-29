        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        class Locs{
        public: 
            int oldLoc;
            int newLoc;
            Locs(int Old=-1,int New=-1): oldLoc(Old), newLoc(New){;}
        };

 
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable(  int size );
            void insert(Locs l);
            void remove(Locs l);
            Locs& find(Locs x);
            Locs* array;
            int size;
            Locs ITEM_NOT_FOUND;
            
        };


        #endif
