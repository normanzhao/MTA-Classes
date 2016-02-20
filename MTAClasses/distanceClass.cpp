#include "distanceClass.h"
#include <math.h>;

double distanceClass::degrad(double d) {
	const double PI = 2 * acos(0.0);
	return d * PI / 180;
}
//modified to return miles
double distanceClass::haverdist(double lat1, double longit1, double lat2, double longit2)
{
	double r = 6371;
	double dlat = degrad(lat2 - lat1);
	double dlongit = degrad(longit2 - longit1);
	double a = sin(dlat / 2)*sin(dlat / 2) +
		cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return r*c*0.621371;
}
