#include "Sphere.hpp"

bool Sphere::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	Vec3 originCenter = ray.origin() - m_center;
	double a = ray.direction().mag_sq();
	double halfB = Vec3::dot(originCenter, ray.direction());
	double c = originCenter.mag_sq() - m_radius * m_radius;
	double discriminant = halfB * halfB - a * c;

	if (discriminant < 0)
		return false;

	double sqrtd = sqrt(discriminant);
	double sol = (-halfB - sqrtd) / a;
	if (sol < tMin || sol > tMax) {
		sol = (-halfB + sqrtd) / a;
		if (sol < tMin || sol > tMax)
			return false;
	}

	record.t = sol;
	record.hitPoint = ray.at(record.t);

	Vec3 normal = (record.hitPoint - m_center) / m_radius;
	record.set_face_normal(ray, normal);

	record.materialPtr = m_materialPtr;

	return true;
}

bool Sphere::bounding_box(AABB& bbox) const {
	if (m_radius >= 0) {
		bbox = AABB(
			m_center - Vec3(m_radius, m_radius, m_radius),
			m_center + Vec3(m_radius, m_radius, m_radius)
		);
	} else {
		bbox = AABB(
			m_center + Vec3(m_radius, m_radius, m_radius),
			m_center - Vec3(m_radius, m_radius, m_radius)
		);
	}

	return true;
}

void Sphere::dump(int indent) const {
	print_indent(indent);
	printf("Sphere( position: [ %lf %lf %lf ], radius: %lf )\n", m_center.x(), m_center.y(), m_center.z(), m_radius);
}
