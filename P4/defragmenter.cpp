#include "defragmenter.h"
#include "DefragRunner.h"
#include "mynew.h"
using namespace std;


Defragmenter::Defragmenter(DiskDrive *diskDrive) :HT(HSIZE),curr_pos(2),ar_cap(1),topind(0)
{
	
	
	for (emptylast = diskDrive->getCapacity()-1;diskDrive->FAT[emptylast];emptylast--);

	get_files(diskDrive);
	
} // Defragmenter()


void Defragmenter::get_files(DiskDrive *diskDrive){

	

	for (int j=0;j<diskDrive->getNumFiles();++j){

		getblocks(diskDrive,diskDrive->directory[j]);

		
	}
	
}


void Defragmenter::getblocks(DiskDrive* diskDrive,DirectoryEntry& file)
{

	int first = file.getFirstBlockID();
	int next;
	while (first!=1){

		DiskBlock* temp = getAct(diskDrive,first);
		next = temp->getNext();
		if (first != curr_pos){
			if (diskDrive->FAT[curr_pos]){
				keep(diskDrive,curr_pos);
			}
			temp->setNext(curr_pos+1);
			diskDrive->writeDiskBlock(temp,curr_pos);
			diskDrive->FAT[curr_pos] = true;
		}

		else{
			if (next!= curr_pos +1){
				temp->setNext(curr_pos+1);
				diskDrive->writeDiskBlock(temp,curr_pos);
				diskDrive->FAT[curr_pos] = true;
			}
		}

		delete temp;
		first = next;
		curr_pos++;
	}

}


DiskBlock* Defragmenter::getAct (DiskDrive* diskDrive,int index){

	DiskBlock* curr;
	Locs l = HT.find(Locs(index));
	int nl = l.newLoc;
	if (nl == -1){

		curr = diskDrive->readDiskBlock(index);
		diskDrive->FAT[index] = false;
		if (index > emptylast)
			emptylast = index;
	}

	else{

		while ((l.newLoc < 1000000) && (HT.find(Locs(l.newLoc))).newLoc != -1){
			HT.remove(l);
			l = HT.find(Locs(l.newLoc));
		}

		if (l.newLoc >= 1000000){
			curr = Arr[l.newLoc - 1000000];
			arr_ST[topind++] = l.newLoc - 1000000;
		}

		else{
			curr = diskDrive->readDiskBlock(l.newLoc);
			diskDrive->FAT[l.newLoc] = false;
			if (emptylast < l.newLoc)
				emptylast = l.newLoc;
		}
	}

	return curr;

}


void Defragmenter::keep(DiskDrive* diskDrive,int index)
{

	DiskBlock* curr =  diskDrive->readDiskBlock(index);
	diskDrive->FAT[index] = false;
	int i;
	if ((ar_cap<ASIZE) || (topind > 0)){

		if (topind> 0){
			i = arr_ST[topind--];
		}
		else{

			i = ar_cap++;
		}

		Arr[i] = curr;
		HT.insert(Locs(index,1000000 + i));
 	}

 	else{

 		diskDrive->writeDiskBlock(curr,emptylast);
 		diskDrive->FAT[emptylast] =true;
 		HT.insert(Locs(index,emptylast));
 		delete curr;
 		for(; diskDrive->FAT[emptylast]; emptylast--);
 	}

}

	

