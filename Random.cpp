#include "Random.h"

double randomDouble(double _lower_bound, double _upper_bound)
{
	double f = (double)rand() / RAND_MAX;
	return _lower_bound + f * (_upper_bound - _lower_bound);
}
//excluding upper_bound
int randomInteger(int _lower_bound, int _upper_bound)
{
	int res = _lower_bound + (rand() * (int)(_upper_bound - _lower_bound) / RAND_MAX);
	if (res == _upper_bound)
		res--;
	return res;
}

