#pragma once

#include "HitRecord.hpp"

class Hittable {
	public:
		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const = 0;
};
