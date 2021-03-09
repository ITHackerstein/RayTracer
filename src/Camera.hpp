#pragma once

#include <iostream>
#include "Math/Ray.hpp"

class Camera {
	public:
		Camera(Vec3 origin, Vec3 lookAt, double verticalFOV, double aspectRatio);

		const Vec3& origin() const { return m_origin; }

		Ray get_ray(double u, double v) const;

	private:
		Vec3 m_origin;
		Vec3 m_imagePlane[4];
};
