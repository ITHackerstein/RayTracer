#pragma once

#include "../Math/Vec3.hpp"

class Texture {
	public:
		virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
};
