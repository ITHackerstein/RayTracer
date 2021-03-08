#pragma once

#include <stddef.h>
#include <iostream>

#ifdef USE_MULTITHREADING
#include <thread>
#endif

#include "Math/Vec3.hpp"
#include "Primitives/HittableList.hpp"
#include "Utils/Random.hpp"
#include "Utils/Math.hpp"
#include "PPM.hpp"
#include "Camera.hpp"
#include "Materials/Material.hpp"

#define MAX_TRACING_DEPTH 50

class Tracer {
	public:
		#ifdef USE_MULTITHREADING
		static constexpr size_t s_numberOfThreads = 4;
		#endif

		Tracer(size_t imageWidth, size_t imageHeight, size_t samplesPerPixel, Camera& camera, HittableList& world);

		#ifdef USE_MULTITHREADING
		void render() { render_multithreaded(); }
		#else
		void render() { render_singlethreaded(); }
		#endif
	private:
		void render_singlethreaded();

		#ifdef USE_MULTITHREADING
		void render_multithreaded();
		#endif

		Vec3 trace_ray(const Ray& ray, int depth);

		PPMImage m_renderImage;
		double m_aspectRatio;
		size_t m_samplesPerPixel;
		Camera m_camera;
		HittableList m_world;
};
