#include <cmath>

bool closeEnough(double value, double target, double interval)
{
	if (abs(target - value) <= interval)
	{
		return true;
	}
	return false;
}