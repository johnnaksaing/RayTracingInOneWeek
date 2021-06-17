//Utilities here
//DAY 7: pi, INF, degree-radian switch, common headers

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <memory>
#include <limits>
#include <random>
#include <assert.h>

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

inline double random_double() {
	// Returns a random real in [0,1).
	static std::random_device rd;
	static std::mt19937 gen(rd());

	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	return dist(gen);

}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max).
	//assert(max >= min);
	return min + (max - min) * random_double();
}

//custom header
#include "ray.h";
#include "vec3.h";

#endif // !UTILITY_H