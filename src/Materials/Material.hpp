#pragma once

#include "../Math/Ray.hpp"

struct HitRecord; // Forward declaration

class Material {
	public:
		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const = 0;
		virtual Vec3 emitted(double u, double v, const Vec3& p) const { return Vec3(0, 0, 0); }
};
