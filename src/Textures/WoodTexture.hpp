#pragma once

#include "Texture.hpp"
#include "../Utils/Perlin.hpp"

class WoodTexture : public Texture {
	public:
		WoodTexture() {}

		WoodTexture(double scale):
			m_scale(scale) {}

		virtual Vec3 value(double u, double v, const Vec3& p) const override {
			auto factor = 0.5 * (1 + sin(m_scale * p.mag() + 2 * m_perlinGenerator.turb(p)));
			Vec3 color1 (139.0 / 255, 69.0 / 255, 18.0 / 255);
			Vec3 color2 (254.0 / 255, 165.0 / 255, 79.0 / 255);
			return Vec3::lerp(color1, color2, factor);
		}

	private:
		Perlin m_perlinGenerator;
		double m_scale { 1 };
};
