#pragma once

#ifndef PI
#define PI (3.1415926535897932385)
#endif

#ifndef INF_DOUBLE
#define INF_DOUBLE (std::numeric_limits<double>::infinity())
#endif

#ifndef EPSILON
#define EPSILON 1e-3
#endif

inline double clamp(double v, double min, double max) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

inline double degrees_to_radians(double d) {
	return d / 180 * PI;
}

inline double radians_to_degrees(double r) {
	return r / PI * 180;
}
