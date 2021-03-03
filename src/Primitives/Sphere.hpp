#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"

class Sphere {
	public:
		Sphere(Vec3 center, double radius):
			m_center(center), m_radius(radius) {}

		bool intersects_ray(const Ray&) const;
	private:
		Vec3 m_center;
		double m_radius;
};
