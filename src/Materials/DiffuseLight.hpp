#pragma once

#include "../Textures/SolidColor.hpp"
#include "Material.hpp"

class DiffuseLight : public Material {
	public:
		DiffuseLight(std::shared_ptr<Texture> emit):
			m_emit(emit) {}

		DiffuseLight(Vec3 color):
			m_emit(std::make_shared<SolidColor>(color)) {}

		virtual bool scatter(const Ray& ray, const HitRecord&, Vec3& attenuation, Ray& scattered) const override {
			return false;
		}

		virtual Vec3 emitted(double u, double v, const Vec3& p) const {
			return m_emit->value(u, v, p);
		}

	private:
		std::shared_ptr<Texture> m_emit;
};
