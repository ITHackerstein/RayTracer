#pragma once

#include <vector>
#include <memory>
#include "Hittable.hpp"

class HittableList : public Hittable {
	public:
		HittableList() {}

		void add(std::shared_ptr<Hittable> obj) { m_objects.push_back(obj); }
		size_t size() const { return m_objects.size(); }

		virtual bool intersects_ray(const Ray&, double tMin, double tMax, HitRecord&) const override;
	private:
		std::vector<std::shared_ptr<Hittable>> m_objects;
};

