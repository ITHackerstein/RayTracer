#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "Hittable.hpp"
#include "../Utils/Logging.hpp"
#include <memory>
#include <stdio.h>

class Sphere : public Hittable {
	public:
		Sphere(Vec3 center, double radius, std::shared_ptr<Material> materialPtr):
			m_center(center), m_radius(radius), m_materialPtr(materialPtr) {}

		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;
	private:
		Vec3 m_center;
		double m_radius;
		std::shared_ptr<Material> m_materialPtr;
};
