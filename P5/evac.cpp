#include <cstdlib>
#include "evac.h"
#include "QueueAr.h"
#include "EvacRunner.h"
#include <iostream>

using namespace std;



Evac::Evac(City *cities, int numCities, int numRoads): numC(numCities),numR(numRoads),q(numCities)
{
	
	adjList = new City2[numCities];
	visited = new bool[numCities];
	for (int i=0;i<numCities;i++){

		int Id = cities[i].ID;
		adjList[Id].ID = Id; 
		adjList[Id].population = cities[Id].population;
		adjList[Id].evacuees = 0;
		adjList[Id].roadCount = cities[Id].roadCount;
		
		adjList[Id].cityroads = new myRoad[adjList[Id].roadCount];

		for (int j=0;j<adjList[Id].roadCount;j++){
			
			adjList[Id].cityroads[j].myID = cities[Id].roads[j].ID;
			adjList[Id].cityroads[j].destID = cities[Id].roads[j].destinationCityID;
			adjList[Id].cityroads[j].peoplePerHour = cities[Id].roads[j].peoplePerHour;
		}
		
	}

	Time = 1;
	

} // Evac()

void Evac::bfs(){
	

	int id;
	
	while (!q.isEmpty()){

		id = q.dequeue();
		if (!visited[id]){
			visited[id] = true;
			for (int j=0;j<adjList[id].roadCount;j++){
				if (!visited[adjList[id].cityroads[j].destID]){
					
					visited[adjList[id].cityroads[j].destID] = true;
					 adjList[adjList[id].cityroads[j].destID].level = 1 + adjList[id].level;
					 q.enqueue(adjList[id].cityroads[j].destID);
				}
			}
		}
	}
}


void Evac::evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes,
    int &routeCount)
{	
	
	memset(visited,false,sizeof(bool)*numC);
	int leftover = 0;
	for (int i=0; i<numEvacs;i++){

		adjList[evacIDs[i]].isEvac = true;
		adjList[evacIDs[i]].level = 0;
		q.enqueue(evacIDs[i]);
		leftover+= adjList[evacIDs[i]].population;

	}

	bfs();
	int currSent=0;
	int totSent=0;
	int currRecd=0;
	int totRecd=0;
	memset(visited,false,sizeof(bool)*numC);
	while (leftover){
		for (int i=0;i<numEvacs;i++){
			visited[evacIDs[i]] = true;
			currSent = adjList[evacIDs[i]].population ;
			for (int j=0;j<adjList[evacIDs[i]].roadCount;j++){

				currSent = adjList[adjList[evacIDs[i]].cityroads[j].destID].population ;
				
				if (currSent == 0){
					break;
				}

				
				if (currSent > adjList[evacIDs[i]].cityroads[j].peoplePerHour - adjList[evacIDs[i]].cityroads[j].currFlow){
					currSent= adjList[evacIDs[i]].cityroads[j].peoplePerHour - adjList[evacIDs[i]].cityroads[j].currFlow;
				}

				if (currSent<minFlow || currSent < minFlow){
					continue;
				}

				currRecd = dfs(adjList[evacIDs[i]].cityroads[j].destID,currSent,evacRoutes,routeCount);
				if (currRecd >= minFlow){

					evacRoutes[routeCount].roadID = adjList[evacIDs[i]].cityroads[j].myID;
					evacRoutes[routeCount].numPeople = currRecd;
					evacRoutes[routeCount].time = Time;
					adjList[evacIDs[i]].cityroads[j].currFlow += currRecd;
					adjList[evacIDs[i]].population-= currRecd;
					leftover-=currRecd;
					totRecd+=currRecd;
					routeCount++;
				}
			}
			visited[evacIDs[i]] = true;
		}
		
	}

	memset(visited,false,sizeof(bool)*numC);
	if (totRecd==0 && minFlow>=1)
		minFlow--;

	totRecd =0;
	currRecd = 0;
	currSent = 0;
	Time++;
		
}

int Evac::dfs(int ID,int currSent,EvacRoute* evacRoutes,int& routeCount){

	int origSent = currSent;
	int currRecd;
	int finalflow = 0;
	if (visited[ID])
		return 0;

	visited[ID] = true;
	for (int j=0;j<adjList[ID].roadCount;j++){
		if (currSent == 0){
			
			break;
		}

		int flow = origSent;
		if (adjList[adjList[ID].cityroads[j].destID].level >= adjList[ID].level){

			if (flow > adjList[ID].cityroads[j].peoplePerHour - adjList[ID].cityroads[j].currFlow){
				flow = adjList[ID].cityroads[j].peoplePerHour - adjList[ID].cityroads[j].currFlow;
			}

			if (flow == 0 || flow < minFlow){
				continue;
			}

			currRecd = dfs(adjList[ID].cityroads[j].destID,flow,evacRoutes,routeCount);
			if (currRecd >= minFlow){

				evacRoutes[routeCount].roadID = adjList[ID].cityroads[j].myID;
				adjList[ID].cityroads[j].currFlow+= currRecd;
				evacRoutes[routeCount].numPeople = currRecd;
				evacRoutes[routeCount].time = Time;
				routeCount++;
			}

		}

	}

	if (!adjList[ID].isEvac && currSent!=0){

		int remaining =adjList[ID].population - adjList[ID].evacuees;
		if (remaining < currSent){
			currSent = remaining;
		}	

		adjList[ID].evacuees += currSent;
		finalflow += currSent;

	}

	if (finalflow!=0){
		visited[ID] = false;
	}

	return finalflow;
}
	
