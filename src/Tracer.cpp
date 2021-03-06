#include "Tracer.hpp"

#include <atomic>

size_t Tracer::s_numberOfThreads = std::thread::hardware_concurrency();

static inline void convert_to_uv(double x, double y, double w, double h, double &u, double &v) {
	u = x / w;
	v = (h - y - 1) / h;
}

Tracer::Tracer(const Tracer::OutputImageOptions& outputOptions, Camera& camera, Vec3 backgroundColor, HittableList& world):
	m_renderImage(outputOptions.imageWidth, outputOptions.imageHeight),
	m_outputFileName(outputOptions.outputFileName),
	m_samplesPerPixel(outputOptions.samplesPerPixel),
	m_camera(std::move(camera)),
	m_backgroundColor(backgroundColor),
	m_world(std::move(world)),
	m_worldBVH(m_world.objects())
{
}

void Tracer::render() {
	std::cout << "[RayTracer] Rendering using " << s_numberOfThreads << " threads\n";

	size_t rowSize = (size_t) ((double) m_renderImage.height() / s_numberOfThreads);

	std::atomic_size_t currentProgress { 0 };
	std::size_t totalPixels = m_renderImage.width() * m_renderImage.height();

	auto worker = [rowSize, this, &currentProgress](size_t rowY) {
		for (size_t y = rowY; y < rowY + rowSize && y < m_renderImage.height(); ++y) {
			for (size_t x = 0; x < m_renderImage.width(); ++x) {
				Vec3 color;
				for (size_t s = 0; s < m_samplesPerPixel; ++s) {
					double u, v;
					convert_to_uv(x + random_double(), y + random_double(), m_renderImage.width(), m_renderImage.height(), u, v);
					Ray ray = m_camera.get_ray(u, v);
					color += trace_ray(ray, MAX_TRACING_DEPTH) / m_samplesPerPixel;
				}

				Vec3 corrected = Vec3(
					clamp(pow(color.x(), 1.0 / 2.2), 0, 1),
					clamp(pow(color.y(), 1.0 / 2.2), 0, 1),
					clamp(pow(color.z(), 1.0 / 2.2), 0, 1)
				);

				auto rgb = PPMImage::rgb_from_vector(corrected);
				m_renderImage.set_pixel(x, y, rgb);
				++currentProgress;
			}
		}
	};

	auto begin = std::chrono::steady_clock::now();

	std::vector<std::thread> threads;
	for (size_t y = 0; y < m_renderImage.height(); y += rowSize) {
		std::cout << "[RayTracer] Creating thread at (X=0, Y=" << y << ")\n";
		threads.emplace_back(worker, y);
	}

	std::thread logger { [&currentProgress, totalPixels]() {
		auto logProgress = [totalPixels](size_t current) {
			float progress = static_cast<float>(current) / totalPixels * 100.0f;
			printf("[RayTracer] Progress: %03.2f %%", progress);
		};

		auto currentProgressValue = currentProgress.load();

		while (currentProgressValue < totalPixels) {
			printf("\r");
			logProgress(currentProgressValue);
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(500ms);

			currentProgressValue = currentProgress.load();
		}

		printf("\r");
		logProgress(currentProgressValue);
		printf("\n");
	} };

	std::cout << "[RayTracer] Waiting for threads to die\n";
	for (auto& t: threads) {
		if (t.joinable())
			t.join();
	}

	logger.join();

	auto end = std::chrono::steady_clock::now();

	std::cout << "[RayTracer] All threads died. Finished rendering! Time took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 << " s\n";

	std::cout << "[RayTracer] Saving to '" << m_outputFileName << "'\n";
	m_renderImage.save(m_outputFileName);
}

Vec3 Tracer::trace_ray(const Ray& ray, int depth) {
	if (depth <= 0)
		return Vec3(0, 0, 0);

	HitRecord record;
	if (!m_worldBVH.intersects_ray(ray, record, m_world.objects()))
		return m_backgroundColor;

	Ray scattered;
	Vec3 attenuation;
	Vec3 emitted = record.materialPtr->emitted(record.u, record.v, record.hitPoint);

	if (!record.materialPtr->scatter(ray, record, attenuation, scattered))
		return emitted;

	return emitted + attenuation * trace_ray(scattered, depth - 1);
}
