#pragma once

#include "Vec3.hpp"

class Ray {
	public:
		Ray() {}
		Ray(const Vec3& origin, const Vec3& direction):
			m_origin(origin), m_direction(direction) {}

		Vec3 origin() { return m_origin; }
		Vec3 direction() { return m_direction; }

		Vec3 at(double t) const { return origin() + t * direction(); }
	private:
		Vec3 m_origin;
		Vec3 m_direction;
};
