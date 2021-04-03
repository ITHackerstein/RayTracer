#pragma once

#include "../Math/Vec3.hpp"
#include "../Primitives/HitRecord.hpp"
#include "../Textures/SolidColor.hpp"
#include "Material.hpp"

class LambertianDiffuse : public Material {
	public:
		LambertianDiffuse(const Vec3& albedo):
			m_albedo(std::make_shared<SolidColor>(albedo)) {}

		LambertianDiffuse(const std::shared_ptr<Texture>& albedo):
			m_albedo(albedo) {}

		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const override;
	private:
		std::shared_ptr<Texture> m_albedo;
};
