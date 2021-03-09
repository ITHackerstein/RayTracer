#include "Camera.hpp"

Camera::Camera(Vec3 origin, Vec3 lookAt, double verticalFOV, double aspectRatio):
	m_origin(origin)
{
	double h = tan(verticalFOV / 2);
	double viewportHeight = 2 * h;
	double viewportWidth = viewportHeight * aspectRatio;

	Vec3 w = Vec3::normalize(m_origin - lookAt);
	Vec3 u = Vec3::normalize(Vec3::cross(Vec3(0, 1, 0), w));
	Vec3 v = Vec3::cross(w, u);

	m_imagePlane[0] = m_origin - viewportWidth * u / 2 - viewportHeight * v / 2 - w; // Bottom-Left Corner
	m_imagePlane[1] = m_origin + viewportWidth * u / 2 - viewportHeight * v / 2 - w; // Bottom-Right Corner
	m_imagePlane[2] = m_origin - viewportWidth * u / 2 + viewportHeight * v / 2 - w; // Top-Left Corner
	m_imagePlane[3] = m_origin + viewportWidth * u / 2 + viewportHeight * v / 2 - w; // Top-Right Corner
}

Ray Camera::get_ray(double u, double v) const {
	Vec3 b = Vec3::lerp(m_imagePlane[0], m_imagePlane[1], u);
	Vec3 t = Vec3::lerp(m_imagePlane[2], m_imagePlane[3], u);
	Vec3 p = Vec3::lerp(b, t, v);

	return Ray(m_origin, p - m_origin);
}
