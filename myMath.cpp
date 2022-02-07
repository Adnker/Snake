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

int Rander::GetARand(int max,int min)
{
	std::uniform_int_distribution<int> u(min, max); // ×ó±ÕÓÒ±ÕÇø¼ä
	e.seed(time(0) + max + min + seek);
	seek = u(e);
	return u(e);
}
