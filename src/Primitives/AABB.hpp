#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"

class AABB {
	public:
		AABB() {}

		AABB(const Vec3& minimum, const Vec3& maximum):
			m_minimum(minimum), m_maximum(maximum) {}

		Vec3 minimum() const { return m_minimum; }
		Vec3 maximum() const { return m_maximum; }

		bool intersects_ray(const Ray&, double tMax) const;

		static AABB surrounding_box(const AABB&, const AABB&);
	private:
		Vec3 m_minimum;
		Vec3 m_maximum;
};
