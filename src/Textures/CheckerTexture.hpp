#pragma once

#include "SolidColor.hpp"
#include <memory>

class CheckerTexture : public Texture {
	public:
		CheckerTexture() {}

		CheckerTexture(const std::shared_ptr<Texture>& odd, const std::shared_ptr<Texture>& even):
			m_odd(odd), m_even(even) {}

		CheckerTexture(Vec3 odd, Vec3 even):
			CheckerTexture(std::make_shared<SolidColor>(odd), std::make_shared<SolidColor>(even)) {}

		virtual Vec3 value(double u, double v, const Vec3& p) const override;

	private:
		std::shared_ptr<Texture> m_odd;
		std::shared_ptr<Texture> m_even;
};
