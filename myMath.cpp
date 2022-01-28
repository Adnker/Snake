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

Rander::Rander()
{
	srand(time(NULL));
	seek = time(NULL) % rand();
	seek = GetARand(seek);
}

int Rander::GetARand(int max)
{
	int rands = 0;
	for (int i = 0; i < seek; i++) {
		rands = rand() % max + 1;
	}
	seek = rands * 17;
	return rands;
}
