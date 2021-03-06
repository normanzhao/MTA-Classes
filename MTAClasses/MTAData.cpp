#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "distanceClass.h";
#include "trainStopData.h";

#include "MTAData.h"
using namespace std;

const int DEFAULT_VAL = -1;      // must be less than 0
const string STANDARD_VAL = "";
distanceClass dist;
//get data
vector<trainStopData> MTAData::getData()
{
	std::vector<trainStopData> trainStopDataVector;
	std::ifstream data;
	data.open("MTA_train_stop_data.txt");
	std::string line;
	getline(data, line); //trash to take out column names
	while (getline(data, line))
	{
		int posA = line.find_first_of(',');
		std::string stopID = (line.substr(0, posA));
		if ((stopID[stopID.size() - 1] != 'N') && (stopID[stopID.size() - 1] != 'S'))
		{
			int posB = line.find_first_of(',', posA + 1);
			posA = line.find_first_of(',', posB + 1);
			std::string stopName = (line.substr(posB + 1, posA - posB - 1));
			posB = line.find_first_of(',', posA + 1);
			posA = line.find_first_of(',', posB + 1);
			double stopLat = std::stod(line.substr(posB + 1, posA - posB - 1));
			posB = line.find_first_of(',', posA + 1);
			double stopLon = std::stod(line.substr(posA + 1, posB - posA - 1));
			trainStopData tSD(stopID, stopName, stopLat, stopLon);
			trainStopDataVector.push_back(tSD);
		}

	}
	data.close();
	return trainStopDataVector;
}
unordered_map<string, list<string>> MTAData::makeList()
{
	unordered_map<string, list<string>> adjList;
	vector<trainStopData> tSDv = getData();
	for (size_t i = 0; i < tSDv.size(); i++)
	{
		list<string> adj;
		if (i == 0)
		{
			if (tSDv[i].get_id()[0] == tSDv[i + 1].get_id()[0])
			{
				adj.push_back(tSDv[i + 1].get_id());
			}
		}
		else if (i == tSDv.size() - 1)
		{
			if (tSDv[i].get_id()[0] == tSDv[i - 1].get_id()[0])
			{
				adj.push_back(tSDv[i - 1].get_id());
			}
		}
		else
		{
			if (tSDv[i].get_id()[0] == tSDv[i - 1].get_id()[0])
			{
				adj.push_back(tSDv[i - 1].get_id());
			}
			if (tSDv[i].get_id()[0] == tSDv[i + 1].get_id()[0])
			{
				adj.push_back(tSDv[i + 1].get_id());
			}
		}
		adjList[tSDv[i].get_id()] = adj;
	}
	ifstream data;
	data.open("transfers.txt");
	string line;
	while (getline(data, line))
	{
		stringstream eachLine(line);
		string from, to;
		getline(eachLine, from, ',');
		getline(eachLine, to, ',');
		if (from != to)
		{
			adjList[from].push_back(to);
		}
	}
	data.close();
	return adjList;
}
//return data based on data string
trainStopData MTAData::search()
{
	cout << "Search by stop name of ID?\n1. Stop name\n2. Stop ID\n";
	int choice = 0;
	while (choice == 0)
	{
		cin >> choice;
		if (choice == 1 || choice == 2)
		{
			string stop;
			if (choice == 1)
			{
				cout << endl << "Stop name(case sensitive): ";
				cin >> stop;
				return findName(stop);
			}
			else
			{
				cout << endl << "Stop ID: ";
				cin >> stop;
				return findID(stop);
			}
		}
		choice = 0;
		cout << "Invalid input, please try again: ";
	}
}
trainStopData MTAData::findName(string stop)
{
	vector<trainStopData> tSDv;
	trainStopData returntSD;
	for (trainStopData tSD : vtSD)
	{
		if (tSD.get_stop_name().find(stop) != string::npos)
		{
			tSDv.push_back(tSD);
		}
	}
	if (tSDv.size() == 0)
	{
		cout << "\nInvalid stop name. Please try again.\n";
		return search();
	}
	else if (tSDv.size() == 1)
	{
		returntSD = tSDv[0];
	}
	else
	{
		for (size_t x = 0; x < tSDv.size(); x++)
		{
			cout << endl << x << ". " << tSDv[x].get_id() << "  " << tSDv[x].get_stop_name();
		}
		int choice = tSDv.size();
		while (choice > tSDv.size()-1)
		{
			cout << endl << endl << "Please select a stop using the numberpad: ";
			cin >> choice;
			returntSD = tSDv[choice];
		}
	}
	return returntSD;
}
trainStopData MTAData::findID(string stop)
{
	vector<trainStopData> tSDv;
	trainStopData returntSD;
	for (trainStopData tSD : vtSD)
	{
		if (tSD.get_id().find(stop) != string::npos)
		{
			tSDv.push_back(tSD);
		}
	}
	if (tSDv.size() == 0)
	{
		cout << "\nInvalid stop id. Please try again.\n";
		return search();
	}
	else if (tSDv.size() == 1)
	{
		returntSD = tSDv[0];
	}
	else
	{
		for (size_t x = 0; x < tSDv.size(); x++)
		{
			cout << endl << x << ". " << tSDv[x].get_id() << "  " << tSDv[x].get_stop_name();
		}
		int choice = tSDv.size();
		while (choice > tSDv.size() - 1)
		{
			cout << endl << endl << "Please select a stop using the numberpad: ";
			cin >> choice;
			returntSD = tSDv[choice];
		}
	}
	return returntSD;
}
//check if stop in enroute 
class MTAData::isStopOnRoute
{
public:
	isStopOnRoute(const char& trainRoute)
	{
		route = trainRoute;
	}
	bool operator()(const trainStopData& tSD)
	{
		if (route == tSD.get_id()[0])
		{
			return true;
		}
		return false;
	}
private:
	char route;
};
//check if stopID exist and is a legitimate stop
class MTAData::isSubwayStop
{
public:
	isSubwayStop(const std::string& stopId)
	{
		stopid = stopId;
	}
	bool operator()(const trainStopData& tSD)
	{
		if (stopid == tSD.get_id())
		{
			return true;
		}
		return false;
	}
private:
	std::string stopid;
};
//calculate distance from stop to another grographic coordinate
class MTAData::isSubwayStopNearX
{
public:
	isSubwayStopNearX(double longitude, double latitute, double d) :checkLong(longitude), checkLat(latitute), distance(d) {}
	bool operator()(const trainStopData& tSD)
	{
		if (dist.haverdist(checkLat, checkLong, tSD.get_latitude(), tSD.get_longitude()) <= distance)
		{
			return true;
		}
		return false;
	}
private:
	double checkLong;
	double checkLat;
	double distance;
};
//prints out information about a specific stop
class MTAData::printTrainStopInfo
{
public:
	void operator()(const trainStopData& tSD)
	{
		std::cout << "Stop ID: " << tSD.get_id() << std::endl << "Stop Name: " << tSD.get_stop_name() << std::endl << "Stop Latitude: " << tSD.get_latitude() << std::endl << "Stop Longitude: " << tSD.get_longitude() << std::endl;
	}
};
//train travel time in minutes
double MTAData::travelTime(double distance)
{
	return (27 / distance) / 60;
}
//calculate distance between 2 stops
double MTAData::stopDistance(trainStopData stop1, trainStopData stop2)
{
	
	if (stop1.get_id() == stop2.get_id() || (stop1.get_id() == "") || (stop2.get_id() == ""))
	{
		return 0;
	}
	return dist.haverdist(stop1.get_latitude(), stop1.get_longitude(), stop2.get_latitude(), stop2.get_longitude());
}
//calculate distance of a route
double MTAData::routeDistance(char route)
{
	
	trainStopData stop1, stop2;
	for (size_t i = 0; i < vtSD.size(); i++)
	{
		if (vtSD[i].get_id()[0] == route)
		{
			stop1 = vtSD[i];
			break;
		}
	}
	for (size_t i = 0; i < vtSD.size(); i++)
	{
		if (vtSD[i].get_id()[0] == route)
		{
			stop2 = vtSD[i];
		}
	}
	if (stop1.get_id() == stop2.get_id() || (stop1.get_id() == "") || (stop2.get_id() == ""))
	{
		return 0;
	}
	return dist.haverdist(stop1.get_latitude(), stop1.get_longitude(), stop2.get_latitude(), stop2.get_longitude());
}
//shortest route
typedef unordered_map < string, list<string>> Graph;        // The graph is given in an adjacency list.
															// Vertices are indexed from 0 to V-1
															// The indices of the vertices adjacent to vertex i
															// are in the list Graph[i].
															// Graph can be directed or undirected.
struct MTAData::vertexInf                    // Stores information for a vertex
{
	int dist;  // distance to vertex from the source
	string prev;  // previous node in BFS tree
};
//function provided
void MTAData::shortestpaths(const Graph & g, string from, string to)
{
	queue<string> q;             // q is the queue of vertex numbers

	if ((g.count(from) == 0) || (g.count(to) == 0))
	{
		cout << "Bad index" << endl;
		return;
	}
	unordered_map<string, vertexInf> vertices(g.size());            // stores BFS info for the vertices
																	// info for vertex j is in position j
	for (auto a : g)
	{
		vertexInf v;
		v.dist = DEFAULT_VAL;
		v.prev = STANDARD_VAL;
		vertices[a.first] = v;
	}
	vertices[from].dist = 0;
	q.push(from);
	while (!q.empty())
	{
		string v = q.front();
		q.pop();
		for (list<string>::const_iterator w = (g.find(v))->second.begin(); w != (g.find(v))->second.end(); w++)
		{

			if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
			{
				vertices[*w].dist = vertices[v].dist + 1;
				vertices[*w].prev = v;
				q.push(*w);
			}
		}
	}
	for (auto v : vertices)        // print distances from source and paths
	{
		if (v.first == to)
		{
			cout << "Total stops: " << v.second.dist << endl;
			cout << endl <<  "Stops: ";
			stack<string> t;

			string current = v.first;
			while (current != STANDARD_VAL)
			{
				t.push(current);
				current = vertices.find(current)->second.prev;
			}
			while (!t.empty())
			{
				cout << t.top() << " ";
				t.pop();
			}
			cout << endl;
		}
	}
}
//map route
void MTAData::mapRoute()
{
	list<char> routes = { '1', '2', '3', '4', '5', '6', '7', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'L', 'M', 'N', 'R', 'S' };
	bool loop = true;
	char choice;
	while (loop == true)
	{
		cout << "Please enter in a route: ";
		cin >> choice;
		for (char letter : routes)
		{
			if (choice == letter)
			{
				loop = false;
			}
		}
	}
	MTAData::isStopOnRoute iSOR(choice);
	cout << endl << endl;
	for (trainStopData tSD : vtSD)
	{
		int x = 1;
		if (iSOR(tSD))
		{
			cout << x << ". " << tSD.get_stop_name() << endl;
			x++;
		}
	}
	cout << endl;
}
//lookup stop
void MTAData::stopLookup()
{
	printTrainStopInfo pTSI;
	trainStopData tSD;
	tSD = search();
	cout << endl << endl;
	pTSI(tSD);
	cout << endl;
}
void MTAData::stopProx()
{
	double lon, lat, dis;
	cout << "Please enter in a longitude: ";
	cin >> lon;
	cout << "Please enter in a latidude: ";
	cin >> lat;
	cout << "Please enter in a distance: ";
	cin >> dis;
	isSubwayStopNearX iSSNX(lon,lat,dis);
	trainStopData tSD = search();
	if (iSSNX(tSD))
	{
		cout << "This stop is within " << dis << " miles of " << lon << "," << lat << "." << endl;
	}
	else
	{
		cout << "This stop is not within " << dis << " miles of " << lon << "," << lat << "." << endl;
		cout << "It is " << dist.haverdist(tSD.get_latitude(), tSD.get_longitude(), lat, lon) - dis << " actually about miles further away"<< endl;
	}

}
//route planner
void MTAData::planRoute()
{
	trainStopData stop1, stop2;
	printTrainStopInfo pTSI;
	cout << "\nFirst stop: \n\n";
	stop1 = search();
	cout << "\nSecond stop: \n\n";
	stop2 = search();
	cout << endl << "Stop 1 information: " << endl;
	pTSI(stop1);
	cout << endl << "Stop 2 information: "<< endl;
	pTSI(stop2);
	cout << endl << "(Transfers): " << endl;
	shortestpaths(utSD, stop1.get_id(), stop2.get_id());
	cout << endl << "Distance between the two stops: " << stopDistance(stop1, stop2) << " mile(s)";
	cout << endl << "Estimated travel time: " << travelTime(stopDistance(stop1, stop2)) << " minute(s)" << endl;
}