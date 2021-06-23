#pragma once

#include "Hittable.hpp"
#include "../Utils/Logging.hpp"
#include "../Math/Transform.hpp"

class Instance : public Hittable {
	public:
		Instance(std::shared_ptr<Hittable> hittableObj, Transform transform):
			m_hittableObj(hittableObj), m_transform(transform) {}

		virtual bool intersects_ray(const Ray&, HitRecord&) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;

	private:
		std::shared_ptr<Hittable> m_hittableObj;
		Transform m_transform;
};
