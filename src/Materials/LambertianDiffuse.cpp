#include "LambertianDiffuse.hpp"

bool LambertianDiffuse::scatter(const Ray& ray, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	Vec3 scatterDirection = record.normal + Vec3::random_in_hemisphere(record.normal);

	// Close to zero scatter directions can create problems with floating point arithmetic.
	if (scatterDirection.near_zero())
		scatterDirection = record.normal;

	scattered = Ray(record.hitPoint, scatterDirection);
	attenuation = m_albedo->value(record.u, record.v, record.hitPoint);
	return true;
}
