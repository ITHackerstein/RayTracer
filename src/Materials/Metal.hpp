#pragma once

#include "../Math/Ray.hpp"
#include "../Primitives/HitRecord.hpp"
#include "Material.hpp"

class Metal : public Material {
	public:
		Metal(const Vec3& albedo, double fuzzyFactor):
			m_albedo(albedo), m_fuzzyFactor(fuzzyFactor) {}

		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const override;
	private:
		Vec3 m_albedo;
		double m_fuzzyFactor;
};
