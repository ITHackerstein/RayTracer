#include "Tracer.hpp"

Tracer::Tracer(size_t imageWidth, size_t imageHeight, Vec3 cameraOrigin, HittableList& world):
	m_renderImage(imageWidth, imageHeight),
	m_aspectRatio((double) imageWidth / imageHeight),
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
			Vec3 color = trace_pixel(x, y);
			auto rgb = PPMImage::rgb_from_vector(color);
			m_renderImage.set_pixel(x, y, rgb);
		}
	}

	m_renderImage.save("render.ppm");
}

Ray Tracer::get_ray(size_t x, size_t y) {
	double u = (double) x / m_renderImage.width();
	double v = (double) (m_renderImage.height() - y - 1) / m_renderImage.height();

	Vec3 b = Vec3::lerp(m_imagePlane[0], m_imagePlane[1], u);
	Vec3 t = Vec3::lerp(m_imagePlane[2], m_imagePlane[3], u);
	Vec3 p = Vec3::lerp(b, t, v);

	return Ray(m_cameraOrigin, p - m_cameraOrigin);
}

Vec3 Tracer::trace_pixel(size_t x, size_t y) {
	Ray ray = get_ray(x, y);

	HitRecord record;
	if (m_world.intersects_ray(ray, 0, INF_DOUBLE, record))
		return 0.5 * (record.normal + Vec3(1, 1, 1));

	double t = 0.5 * (ray.direction().y + 1);
	return Vec3::lerp(Vec3(0.85, 0.85, 0.85), Vec3(0.56, 0.81, 1), t);
}
