#pragma once

#include "Hittable.hpp"
#include "Triangle.hpp"
#include "BVH.hpp"

class Mesh : public Hittable {
	public:
		Mesh(const std::vector<std::shared_ptr<Triangle>>& faces, const std::shared_ptr<Material>& materialPtr):
			m_faces(std::vector<std::shared_ptr<Hittable>>(faces.begin(), faces.end())),
			m_facesBVH(m_faces),
			m_materialPtr(materialPtr)
		{}

		virtual bool intersects_ray(const Ray&, HitRecord&) const override;
		virtual bool center(Vec3& center) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;

	private:
		std::vector<std::shared_ptr<Hittable>> m_faces;
		BVH m_facesBVH;
		std::shared_ptr<Material> m_materialPtr;
};
