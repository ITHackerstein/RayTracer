#pragma once

#include "Texture.hpp"

class SolidColor : public Texture {
	public:
		SolidColor() {}
		SolidColor(Vec3 color):
			m_color(color) {}

		SolidColor(double r, double g, double b):
			m_color(r, g, b) {}

		virtual Vec3 value(double u, double v, const Vec3& p) const override {
			return m_color;
		}
	private:
		Vec3 m_color;
};
