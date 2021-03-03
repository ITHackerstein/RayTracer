#include "Sphere.hpp"

bool Sphere::intersects_ray(const Ray& ray) const {
	Vec3 originCenter = ray.origin() - m_center;
	double a = Vec3::dot(ray.direction(), ray.direction());
	double b = 2 * Vec3::dot(originCenter, ray.direction());
	double c = Vec3::dot(originCenter, originCenter) - m_radius * m_radius;
	double discriminant = b * b - 4 * a * c;

	return discriminant > 0;
}
