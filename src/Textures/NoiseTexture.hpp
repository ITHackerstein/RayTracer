#pragma once

#include "Texture.hpp"
#include "../Utils/Perlin.hpp"

class NoiseTexture : public Texture {
	public:
		NoiseTexture() {}

		NoiseTexture(double scale):
			m_scale(scale) {}

		virtual Vec3 value(double u, double v, const Vec3& p) const override {
			return Vec3(1, 1, 1) * (0.5 * (1 + sin(m_scale * p.z() + 10 * m_perlinGenerator.turb(p))));
		}

	private:
		Perlin m_perlinGenerator;
		double m_scale { 1 };
};
