#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "Hittable.hpp"
#include "../Utils/Logging.hpp"
#include "../Utils/Math.hpp"
#include <memory>
#include <stdio.h>

class Sphere : public Hittable {
	public:
		Sphere(double radius, std::shared_ptr<Material> materialPtr):
			m_radius(radius), m_materialPtr(materialPtr) {}

		virtual bool intersects_ray(const Ray&, HitRecord&) const override;
		virtual bool center(Vec3& center) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;
	private:
		static void get_uv(const Vec3& p, double& u, double& v);

		double m_radius;
		std::shared_ptr<Material> m_materialPtr;
};
