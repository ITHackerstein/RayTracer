#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "Hittable.hpp"

class Sphere : public Hittable {
	public:
		Sphere(Vec3 center, double radius):
			m_center(center), m_radius(radius) {}

		bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
	private:
		Vec3 m_center;
		double m_radius;
};
