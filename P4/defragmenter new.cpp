#include "defragmenter.h"
#include "DefragRunner.h"
#include "mynew.h"
#include <iostream>
using namespace std;

#define ARR_SIZE 12000
Defragmenter::Defragmenter(DiskDrive *diskDrive) :HT(500001), 
stack(ARR_SIZE)

{
	
	Arr = new DiskBlock*[ARR_SIZE];
	empty_last = diskDrive->getCapacity() -1;
	for (short i=ARR_SIZE-1;i>=0;i--){
		stack.push(i);
	}
	
	arrangeBlocks(diskDrive);
	put_empty_last(diskDrive);
	
	diskDrive->Print();
	
} // Defragmenter()



void Defragmenter::arrangeBlocks(DiskDrive* diskDrive){

//	diskDrive->Print();

	int Old=-1;
  	int New=-1;
  	int current_position=2;
  	
  	for (int i=0;i<diskDrive->getNumFiles();++i){


  		Old = diskDrive->directory[i].getFirstBlockID();
  		int filesize = diskDrive->directory[i].getSize();
  		for (int j=0;j<filesize;++j){


  			DiskBlock* curr;
  			DiskBlock* temp;

  			 int res = HT.find(Old);
         //cout<<Old<<endl;
          while(res!=-1){
           
            Old = New;
             HT.remove(Old);
            New = res;
            res = HT.find(res);
          }

          if (New >= 1000000){ //RAM
            New-= 1000000;
            curr = Arr[New];
            stack.push(New);
          }

          else{//Drive

            curr = diskDrive->readDiskBlock(New);
            diskDrive->FAT[New] = false;
          }

  				
  				
  			

  			if (!diskDrive->FAT[current_position]){

  				diskDrive->FAT[current_position] = true;
  				HT.remove(Old);
  				Old = curr->getNext();
          
  			}

  			else{

  				temp = diskDrive->readDiskBlock(current_position);
				
          if (!stack.isEmpty()){

					Arr[stack.top()] = curr;
					HT.insert(current_position,1000000+stack.top());
					stack.pop();
					delete temp;
				}

				else{

					if (empty_last < New){

						empty_last = New;
						diskDrive->FAT[New] = false;
					}

					while(diskDrive->FAT[empty_last]){

						empty_last--;
					}

					diskDrive->FAT[empty_last] = true;
					diskDrive->writeDiskBlock(temp,empty_last);
					delete temp;
				}
  		}

  			diskDrive->writeDiskBlock(curr,current_position);
  			Old = curr->getNext();
  			++current_position;
        //delete curr;
  		}
  	}
}



void Defragmenter::put_empty_last(DiskDrive* diskDrive){
	
	delete[] Arr;
	HT.callatend();
}
