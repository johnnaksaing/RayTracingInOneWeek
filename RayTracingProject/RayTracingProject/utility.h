//Utilities here
//DAY 7: pi, INF, degree-radian switch, common headers

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <memory>
#include <limits>

//usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constants
const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();


//utility function
inline double degrees_to_radian(double degree) {
	return degree * pi / 180.0;
}

//custom header
#include "ray.h";
#include "vec3.h";

#endif // !UTILITY_H