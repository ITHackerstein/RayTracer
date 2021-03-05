#pragma once

#include <stddef.h>
#include <stdio.h>
#include "Math/MathDefs.hpp"
#include "Math/Vec3.hpp"
#include "Primitives/HittableList.hpp"
#include "Utils/Random.hpp"
#include "PPM.hpp"

#define MAX_TRACING_DEPTH 50

class Tracer {
	public:
		Tracer(size_t imageWidth, size_t imageHeight, size_t samplesPerPixel, Vec3 cameraOrigin, HittableList& world);

		void render();
	private:
		Vec3 trace_ray(const Ray& ray, int depth);
		Ray get_ray(double x, double y);

		PPMImage m_renderImage;
		double m_aspectRatio;
		size_t m_samplesPerPixel;
		Vec3 m_imagePlane[4];
		Vec3 m_cameraOrigin;
		HittableList m_world;
};
