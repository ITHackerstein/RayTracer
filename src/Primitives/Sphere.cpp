#include "Sphere.hpp"

bool Sphere::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	Vec3 originCenter = ray.origin() - m_center;
	double a = Vec3::dot(ray.direction(), ray.direction());
	double halfB = Vec3::dot(originCenter, ray.direction());
	double c = Vec3::dot(originCenter, originCenter) - m_radius * m_radius;
	double discriminant = halfB * halfB - a * c;

	if (discriminant < 0)
		return false;

	double sqrtd = sqrt(discriminant);
	double sol = (-halfB - sqrtd) / a;
	if (sol < tMin || sol > tMax) {
		sol = (-halfB + sqrtd) / a;
		if (sol < tMin || sol > tMax)
			return false;
	}

	record.t = sol;
	record.hitPoint = ray.at(record.t);
	record.normal = Vec3::normalize((record.hitPoint - m_center) / m_radius);

	return true;
}
