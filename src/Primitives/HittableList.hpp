#pragma once

#include <vector>
#include <memory>
#include "Hittable.hpp"
#include "../Utils/Logging.hpp"

class HittableList : public Hittable {
	public:
		HittableList() {}

		void add(std::shared_ptr<Hittable> obj) { m_objects.push_back(obj); }
		size_t size() const { return m_objects.size(); }
		const std::vector<std::shared_ptr<Hittable>>& objects() const { return m_objects; }

		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
		virtual bool bounding_box(AABB& bbox) const override;
		virtual void dump(int indent) const override;
	private:
		std::vector<std::shared_ptr<Hittable>> m_objects;
};

