#pragma once

#include "../Math/Vec3.hpp"
#include "../Primitives/HitRecord.hpp"
#include "Material.hpp"

class LambertianDiffuse : public Material {
	public:
		LambertianDiffuse(const Vec3& color):
			m_albedo(color) {}

		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const override;
	private:
		Vec3 m_albedo;
};
