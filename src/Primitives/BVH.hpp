#pragma once

#include "../Math/Ray.hpp"
#include "../Utils/Random.hpp"
#include "HittableList.hpp"
#include "AABB.hpp"
#include <assert.h>
#include <algorithm>

class BVHNode : public Hittable {
	public:
		BVHNode() {};

		BVHNode(const HittableList& hlist):
			BVHNode(hlist.objects(), 0, hlist.size()) {};

		BVHNode(const std::vector<std::shared_ptr<Hittable>>& objects, size_t low, size_t high);

		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;

	private:
		std::shared_ptr<Hittable> m_left;
		std::shared_ptr<Hittable> m_right;
		AABB m_bbox;
};
