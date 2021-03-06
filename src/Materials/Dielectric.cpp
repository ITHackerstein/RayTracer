#include "Dielectric.hpp"

bool Dielectric::scatter(const Ray& ray, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	attenuation = Vec3(1, 1, 1);
	double relativeRefractiveIndex = record.isOut ? 1 / m_refractiveIndex : m_refractiveIndex;
	Vec3 normDirection = Vec3::normalize(ray.direction());
	double cosT = fmin(Vec3::dot(-normDirection, record.normal), 1);
	double sinT = sqrt(1 - cosT * cosT);

	bool cannotRefract = relativeRefractiveIndex * sinT > 1;
	Vec3 rayDirection;
	if (cannotRefract || reflectance(cosT, relativeRefractiveIndex) > random_double())
		rayDirection = Vec3::reflect(normDirection, record.normal);
	else
		rayDirection = Vec3::refract(normDirection, record.normal, relativeRefractiveIndex);

	scattered = Ray(record.hitPoint, rayDirection);
	return true;
}

double Dielectric::reflectance(double cosine, double refractiveIndex) {
	// Schlick's approximation
	double r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 *= r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}
