#include "AABB.hpp"

bool AABB::intersects_ray(const Ray& ray, double tMax) const {
	double tMin = 0;
	for (size_t axis = 0; axis < 3; ++axis) {
		double invD = 1.0 / ray.direction()[axis];
		double t0 = (m_minimum[axis] - ray.origin()[axis]) * invD;
		double t1 = (m_maximum[axis] - ray.origin()[axis]) * invD;
		if (invD < 0.0)
			std::swap(t0, t1);

		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;

		if (tMax <= tMin)
			return false;
	}
	return true;
}

AABB AABB::surrounding_box(const AABB& b1, const AABB& b2) {
	Vec3 small(
		fmin(b1.minimum().x(), b2.minimum().x()),
		fmin(b1.minimum().y(), b2.minimum().y()),
		fmin(b1.minimum().z(), b2.minimum().z())
	);

	Vec3 big(
		fmax(b1.maximum().x(), b2.maximum().x()),
		fmax(b1.maximum().y(), b2.maximum().y()),
		fmax(b1.maximum().z(), b2.maximum().z())
	);

	return AABB(small, big);
}
