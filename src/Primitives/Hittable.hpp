#pragma once

#include "HitRecord.hpp"
#include "AABB.hpp"

class Hittable {
	public:
		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const = 0;
		virtual bool bounding_box(AABB& bbox) const = 0;
		virtual void dump(int indent) const = 0;
};
