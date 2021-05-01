#pragma once

#include "Hittable.hpp"
#include "../Utils/Math.hpp"
#include "../Utils/Logging.hpp"

class Triangle : public Hittable {
	public:
		Triangle() {}

		Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, std::shared_ptr<Material> materialPtr):
			m_v0(v0), m_v1(v1), m_v2(v2), m_hasNormals(false), m_materialPtr(materialPtr) {}

		Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2,
		         const Vec3& n0, const Vec3& n1, const Vec3& n2,
		         std::shared_ptr<Material> materialPtr):
			m_v0(v0), m_v1(v1), m_v2(v2), m_hasNormals(true), m_n0(n0), m_n1(n1), m_n2(n2), m_materialPtr(materialPtr) {}

		virtual bool intersects_ray(const Ray &, double tMin, double tMax, HitRecord &) const override;
		virtual bool bounding_box(AABB &bbox) const override;
		virtual void dump(int indent) const override;

	private:
		Vec3 m_v0;
		Vec3 m_v1;
		Vec3 m_v2;

		bool m_hasNormals;
		Vec3 m_n0;
		Vec3 m_n1;
		Vec3 m_n2;

		std::shared_ptr<Material> m_materialPtr;
};
