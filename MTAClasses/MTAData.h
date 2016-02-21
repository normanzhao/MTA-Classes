#pragma once
#include <string>;
#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>

#include "trainStopData.h";
using namespace std;

class MTAData
{
public:
	//get data
	vector<trainStopData> getData();
	unordered_map<string, list<string>> makeList();
	//return data based on data string
	trainStopData find(string stop);
	//check if stop in enroute 
	class isStopOnRoute;
	//check if stopID exist and is a legitimate stop
	class isSubwayStop;
	//calculate distance from stop to another grographic coordinate
	class isSubwayStopNearX;
	//prints out information about a specific stop
	class printTrainStopInfo;
	//train travel time in minutes
	double travelTime(double distance);
	//calculate distance between 2 stops
	double stopDistance(string id1, string id2);
	//calculate distance of a route
	double routeDistance(char route);
	//shortest route
	typedef unordered_map < string, list<string>> Graph;
	struct vertexInf;                    // Stores information for a vertex

	void shortestpaths(const Graph & g, string from, string to);
	//route planner
	void planRoute();
private:
	vector<trainStopData> vtSD = getData();
	unordered_map<string, list<string>> utSD = makeList();
};