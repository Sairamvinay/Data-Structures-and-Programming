// Author: Sean Davis
#ifndef evacH
#define evacH

#include "EvacRunner.h"
#include "QueueAr.h"

class myRoad{

public:

	int destID;
	int srcID;
	int peoplePerHour;
	int myID;
	int currFlow;
	myRoad(){

		peoplePerHour = 0;
		srcID=0;
		currFlow = 0;
	}
};

class City2{

public:
	int ID;
	int population;
	int roadCount;
	int evacuees;
	myRoad* cityroads;
	int level;
	bool isEvac;

	City2(){

		isEvac = 0;
		level = 0;
		
	}
};

class Evac
{

public:
	City2* adjList;
	int numC;
	int numR;
	int Time;
	Queue q;
	EvacRoute* routes;
	bool* visited;
	int minFlow = 30;
  Evac(City *cities, int numCities, int numRoads);
  void evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes,
    int &routeCount); // student sets evacRoutes and routeCount
void bfs();
int dfs(int ID,int currSent,EvacRoute* evacRoutes,int& roadCount); 
}; 


#endif
