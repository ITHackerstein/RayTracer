#pragma once

#include "../Math/Vec3.hpp"

struct HitRecord {
	Vec3 hitPoint;
	Vec3 normal;
	double t;
};
