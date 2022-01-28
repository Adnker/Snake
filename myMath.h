#pragma once
#include <iostream>

class Rander {
public:
	Rander();
	int GetARand(int max);
private:
	int seek;
};

double distance(double x1, double y1, double x2, double y2);