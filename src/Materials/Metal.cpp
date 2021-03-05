#include "Metal.hpp"

bool Metal::scatter(const Ray& ray, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	Vec3 reflected = Vec3::reflect(Vec3::normalize(ray.direction()), record.normal);
	scattered = Ray(record.hitPoint, reflected + m_fuzzyFactor * Vec3::random_in_unit_sphere());
	attenuation = m_albedo;
	return Vec3::dot(scattered.direction(), record.normal) > 0;
}
