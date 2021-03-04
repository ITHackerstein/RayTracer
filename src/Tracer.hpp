#pragma once

#include <stddef.h>
#include <stdio.h>
#include "Math/MathDefs.hpp"
#include "Math/Vec3.hpp"
#include "Primitives/HittableList.hpp"
#include "PPM.hpp"

class Tracer {
	public:
		Tracer(size_t imageWidth, size_t imageHeight, Vec3 cameraOrigin, HittableList& world);

		void render();
	private:
		Vec3 trace_pixel(size_t x, size_t y);
		Ray get_ray(size_t x, size_t y);

		PPMImage m_renderImage;
		double m_aspectRatio;
		Vec3 m_imagePlane[4];
		Vec3 m_cameraOrigin;
		HittableList m_world;
};
