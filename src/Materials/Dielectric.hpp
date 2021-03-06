#pragma once

#include "Material.hpp"
#include "../Primitives/HitRecord.hpp"
#include "../Utils/Random.hpp"

class Dielectric : public Material {
	public:
		Dielectric(double refractiveIndex):
			m_refractiveIndex(refractiveIndex) {}

		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const override;

	private:
		static double reflectance(double cosine, double refractiveIndex);

		double m_refractiveIndex;
};
