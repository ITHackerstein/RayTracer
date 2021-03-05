#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "Hittable.hpp"
#include <memory>

class Sphere : public Hittable {
	public:
		Sphere(Vec3 center, double radius, std::shared_ptr<Material> materialPtr):
			m_center(center), m_radius(radius), m_materialPtr(materialPtr) {}

		bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
	private:
		Vec3 m_center;
		double m_radius;
		std::shared_ptr<Material> m_materialPtr;
};
