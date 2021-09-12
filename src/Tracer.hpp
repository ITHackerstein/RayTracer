#pragma once

#include <stddef.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Math/Vec3.hpp"
#include "Primitives/HittableList.hpp"
#include "Primitives/BVH.hpp"
#include "Utils/Random.hpp"
#include "Utils/Math.hpp"
#include "PPM.hpp"
#include "Camera.hpp"
#include "Materials/Material.hpp"

#define MAX_TRACING_DEPTH 50

class Tracer {
	public:
		struct OutputImageOptions {
			size_t imageWidth;
			size_t imageHeight;
			size_t samplesPerPixel;
			const char* outputFileName;
		};

		Tracer(const OutputImageOptions& outputOptions, Camera& camera, Vec3 backgroundColor, HittableList& world);

		void render();
	private:
		static size_t s_numberOfThreads;

		Vec3 trace_ray(const Ray& ray, int depth);

		PPMImage m_renderImage;
		const char* m_outputFileName;
		double m_aspectRatio;
		size_t m_samplesPerPixel;
		Camera m_camera;
		Vec3 m_backgroundColor;
		HittableList m_world;
		BVH m_worldBVH;
};
