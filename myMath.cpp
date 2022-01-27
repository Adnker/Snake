#include "myMath.h"
#include <math.h>

double distance(double x1,double y1,double x2,double y2)
{
	double distance = sqrt((
			(x1 - x2) * (x1 - x2) +
			(y1 - y2) * (y1 - y2)
			));
	return distance;
}
