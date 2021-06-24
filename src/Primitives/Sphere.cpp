#include "Sphere.hpp"

bool Sphere::intersects_ray(const Ray& ray, HitRecord& record) const {
	double a = ray.direction().mag_sq();
	double halfB = Vec3::dot(ray.origin(), ray.direction());
	double c = ray.origin().mag_sq() - m_radius * m_radius;
	double discriminant = halfB * halfB - a * c;

	if (discriminant < 0)
		return false;

	double sqrtd = sqrt(discriminant);
	double sol = (-halfB - sqrtd) / a;
	if (sol < EPSILON || sol > record.distance) {
		sol = (-halfB + sqrtd) / a;
		if (sol < EPSILON || sol > record.distance)
			return false;
	}

	record.distance = sol;
	record.hitPoint = ray.at(record.distance);

	Vec3 normal = record.hitPoint / m_radius;
	record.set_face_normal(ray, normal);

	get_uv(normal, record.u, record.v);

	record.materialPtr = m_materialPtr;

	return true;
}

bool Sphere::center(Vec3& center) const {
	center = Vec3(0, 0, 0);
	return true;
}

bool Sphere::bounding_box(AABB& bbox) const {
	if (m_radius >= 0) {
		bbox = AABB(
			-Vec3(m_radius, m_radius, m_radius),
			Vec3(m_radius, m_radius, m_radius)
		);
	} else {
		bbox = AABB(
			Vec3(m_radius, m_radius, m_radius),
			-Vec3(m_radius, m_radius, m_radius)
		);
	}

	return true;
}

void Sphere::dump(int indent) const {
	print_indent(indent);
	printf("Sphere( radius: %lf )\n", m_radius);
}

void Sphere::get_uv(const Vec3& p, double& u, double& v) {
	auto theta = acos(-p.y());
	auto phi = atan2(-p.z(), p.x()) + PI;

	u = phi / (2 * PI);
	v = theta / PI;
}
