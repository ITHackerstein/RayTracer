#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "../Utils/Math.hpp"

class AABB {
	public:
		AABB() {}

		AABB(const Vec3& minimum, const Vec3& maximum):
			m_minimum(minimum), m_maximum(maximum) {}

		Vec3 minimum() const { return m_minimum; }
		Vec3 maximum() const { return m_maximum; }

		double area() const;

		bool intersects_ray(const Ray&, double tMax, double& t) const;
		bool intersects_ray(const Ray&, double tMax) const;

		static AABB surrounding_box(const AABB&, const AABB&);
		static inline AABB empty() {
			return { Vec3(INF_DOUBLE, INF_DOUBLE, INF_DOUBLE), Vec3(-INF_DOUBLE, -INF_DOUBLE, -INF_DOUBLE) };
		}
	private:
		Vec3 m_minimum;
		Vec3 m_maximum;
};
