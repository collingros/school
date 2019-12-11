/*
   collin gros
   12/07/2019
*/


#include <limits> // inf
#include <complex> // abs


bool double_equal(double a, double b)
// return true if a and b are equal doubles
{
	if (std::isinf(a) && std::isinf(b)) {
		return true;
	}

	double epsilon = 0.001;
	return std::abs(a - b) < epsilon;
}

