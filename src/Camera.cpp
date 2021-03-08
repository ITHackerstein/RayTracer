#include "Camera.hpp"

Camera::Camera(Vec3 origin, double verticalFOV, double aspectRatio, double focalLength):
	m_origin(origin)
{
	double h = tan(verticalFOV / 2);
	double viewportHeight = 2 * h;
	double viewportWidth = viewportHeight * aspectRatio;

	m_imagePlane[0] = Vec3(-viewportWidth / 2, -viewportHeight / 2, -focalLength); // Bottom-Left Corner
	m_imagePlane[1] = Vec3( viewportWidth / 2, -viewportHeight / 2, -focalLength); // Bottom-Right Corner
	m_imagePlane[2] = Vec3(-viewportWidth / 2,  viewportHeight / 2, -focalLength); // Top-Left Corner
	m_imagePlane[3] = Vec3( viewportWidth / 2,  viewportHeight / 2, -focalLength); // Top-Right Corner
}

Ray Camera::get_ray(double u, double v) const {
	Vec3 b = Vec3::lerp(m_imagePlane[0], m_imagePlane[1], u);
	Vec3 t = Vec3::lerp(m_imagePlane[2], m_imagePlane[3], u);
	Vec3 p = Vec3::lerp(b, t, v);

	return Ray(m_origin, p - m_origin);
}
