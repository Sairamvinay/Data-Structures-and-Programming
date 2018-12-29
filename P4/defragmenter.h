// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH

#include "mynew.h"
#include "DefragRunner.h"
#include "QuadraticProbing.h"
#define HSIZE 200000
#define ASIZE 12000
class Defragmenter
{

public:
  
  QuadraticHashTable HT; 
  DiskBlock* Arr[ASIZE];
  int arr_ST[ASIZE];
  int topind;
  int emptylast;
  int curr_pos;
  int ar_cap;

  explicit Defragmenter(DiskDrive *diskDrive);
  //DiskDrive obj to store this
 
 void get_files(DiskDrive *diskDrive);
 void getblocks(DiskDrive* diskDrive,DirectoryEntry& file);
 DiskBlock* getAct (DiskDrive* diskDrive,int index);
 void keep(DiskDrive* diskDrive,int index);
}; // class Defragmenter


#endif
