#include "Tracer.hpp"

Tracer::Tracer(size_t imageWidth, size_t imageHeight, size_t samplesPerPixel, Vec3 cameraOrigin, HittableList& world):
	m_renderImage(imageWidth, imageHeight),
	m_aspectRatio((double) imageWidth / imageHeight),
	m_samplesPerPixel(samplesPerPixel),
	m_cameraOrigin(cameraOrigin),
	m_world(std::move(world))
{
	// FIXME: Right now we assume that the aspect ratio is greater or equal to 1 meaning that the image width is greater than the image height.

	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * m_aspectRatio;
	double focalLength = 3.0;

	m_imagePlane[0] = Vec3(-viewportWidth / 2, -viewportHeight / 2, -focalLength); // Bottom-Left Corner
	m_imagePlane[1] = Vec3( viewportWidth / 2, -viewportHeight / 2, -focalLength); // Bottom-Right Corner
	m_imagePlane[2] = Vec3(-viewportWidth / 2,  viewportHeight / 2, -focalLength); // Top-Left Corner
	m_imagePlane[3] = Vec3( viewportWidth / 2,  viewportHeight / 2, -focalLength); // Top-Right Corner
}

void Tracer::render() {
	for (size_t y = 0; y < m_renderImage.height(); ++y) {
		for (size_t x = 0; x < m_renderImage.width(); ++x) {
			Vec3 color;
			for (size_t s = 0; s < m_samplesPerPixel; ++s) {
				Ray ray = get_ray(x + random_double(), y + random_double());
				color += trace_ray(ray, MAX_TRACING_DEPTH) / m_samplesPerPixel;
			}

			Vec3 corrected = Vec3(
				clamp(pow(color.x, 1.0 / 2.2), 0, 1),
				clamp(pow(color.y, 1.0 / 2.2), 0, 1),
				clamp(pow(color.z, 1.0 / 2.2), 0, 1)
			);

			auto rgb = PPMImage::rgb_from_vector(corrected);
			m_renderImage.set_pixel(x, y, rgb);
		}
	}

	m_renderImage.save("render.ppm");
}

Ray Tracer::get_ray(double x, double y) {
	double u = (double) x / m_renderImage.width();
	double v = (double) (m_renderImage.height() - y - 1) / m_renderImage.height();

	Vec3 b = Vec3::lerp(m_imagePlane[0], m_imagePlane[1], u);
	Vec3 t = Vec3::lerp(m_imagePlane[2], m_imagePlane[3], u);
	Vec3 p = Vec3::lerp(b, t, v);

	return Ray(m_cameraOrigin, p - m_cameraOrigin);
}

Vec3 Tracer::trace_ray(const Ray& ray, int depth) {
	if (depth <= 0)
		return Vec3(0, 0, 0);

	HitRecord record;
	if (m_world.intersects_ray(ray, 0, INF_DOUBLE, record)) {
		Vec3 target = record.hitPoint + record.normal + Vec3::random_in_unit_sphere();
		return 0.5 * trace_ray(Ray(record.hitPoint, target - record.hitPoint), depth - 1);
	}

	double t = 0.5 * (ray.direction().y + 1);
	return Vec3::lerp(Vec3(0.85, 0.85, 0.85), Vec3(0.56, 0.81, 1), t);
}
