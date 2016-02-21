#include "trainStopData.h"

using namespace std;

trainStopData::trainStopData() {};
trainStopData::trainStopData(const string& id, const string& name, double lat, double lon) : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {}
string trainStopData::get_id()         const { return stop_id; }
string trainStopData::get_stop_name()  const { return stop_name; }
double trainStopData::get_latitude()   const { return stop_lat; }
double trainStopData::get_longitude()  const { return stop_lon; }
