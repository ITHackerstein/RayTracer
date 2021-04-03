#include "CheckerTexture.hpp"

Vec3 CheckerTexture::value(double u, double v, const Vec3& p) const {
	double sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
	if (sines < 0)
		return m_odd->value(u, v, p);
	else
		return m_even->value(u, v, p);
}
