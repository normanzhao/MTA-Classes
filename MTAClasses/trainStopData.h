#pragma once
#include <string>
using namespace std;
class trainStopData
{
public:
	trainStopData();
	trainStopData(const string& id, const string& name, double lat, double lon);
	string trainStopData::get_id()         const;
	string trainStopData::get_stop_name()  const;
	double trainStopData::get_latitude()   const;
	double trainStopData::get_longitude()  const;
private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
};

