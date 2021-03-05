#pragma once

#ifndef PI
#define PI (3.1415926535897932385)
#endif

#ifndef INF_DOUBLE
#define INF_DOUBLE (std::numeric_limits<double>::infinity())
#endif

inline double clamp(double v, double min, double max) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}
