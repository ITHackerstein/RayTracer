#include "Rectangles.hpp"

bool XYRect::intersects_ray(const Ray& ray, HitRecord& record) const {
	double t = -ray.origin().z() / ray.direction().z();
	if (t < EPSILON || t > record.distance)
		return false;

	double x = ray.origin().x() + t * ray.direction().x();
	if (x < -m_width / 2 || x > m_width / 2)
		return false;

	double y = ray.origin().y() + t * ray.direction().y();
	if (y < -m_height / 2 || y > m_height / 2)
		return false;

	record.u = (x + m_width / 2) / m_width;
	record.v = (y + m_height / 2) / m_height;

	Vec3 outNormal = Vec3(0, 0, 1);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.distance = t;
	record.hitPoint = ray.at(record.distance);

	return true;
}

bool XYRect::center(Vec3 &center) const {
	center = Vec3(0, 0, 0);
	return true;
}

bool XYRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(-m_width / 2, -m_height / 2, -EPSILON), Vec3(m_width / 2, m_height / 2, EPSILON));
	return true;
}

void XYRect::dump(int indent) const {
	print_indent(indent);
	printf("XYRect(width=%lf, height=%lf)\n", m_width, m_height);
}

bool XZRect::intersects_ray(const Ray& ray, HitRecord& record) const {
	double t = -ray.origin().y() / ray.direction().y();
	if (t < EPSILON || t > record.distance)
		return false;

	double x = ray.origin().x() + t * ray.direction().x();
	if (x < -m_width / 2 || x > m_width / 2)
		return false;

	double z = ray.origin().z() + t * ray.direction().z();
	if (z < -m_height / 2 || z > m_height / 2)
		return false;

	record.u = (x + m_width / 2) / m_width;
	record.v = (z + m_height / 2) / m_height;

	Vec3 outNormal = Vec3(0, 1, 0);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.distance = t;
	record.hitPoint = ray.at(record.distance);

	return true;
}

bool XZRect::center(Vec3 &center) const {
	center = Vec3(0, 0, 0);
	return true;
}

bool XZRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(-m_width / 2, -EPSILON, -m_height / 2), Vec3(m_width / 2, EPSILON, m_height / 2));
	return true;
}

void XZRect::dump(int indent) const {
	print_indent(indent);
	printf("XZRect(width=%lf, height=%lf)\n", m_width, m_height);
}

bool YZRect::intersects_ray(const Ray& ray, HitRecord& record) const {
	double t = -ray.origin().x() / ray.direction().x();
	if (t < EPSILON || t > record.distance)
		return false;

	double y = ray.origin().y() + t * ray.direction().y();
	if (y < -m_width / 2 || y > m_width / 2)
		return false;

	double z = ray.origin().z() + t * ray.direction().z();
	if (z < -m_height / 2 || z > m_height / 2)
		return false;

	record.u = (y + m_width / 2) / m_width;
	record.v = (z + m_height / 2) / m_height;

	Vec3 outNormal = Vec3(1, 0, 0);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.distance = t;
	record.hitPoint = ray.at(record.distance);

	return true;
}

bool YZRect::center(Vec3 &center) const {
	center = Vec3(0, 0, 0);
	return true;
}

bool YZRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(-EPSILON, -m_width / 2, -m_height / 2), Vec3(EPSILON, m_width / 2, m_height / 2));
	return true;
}

void YZRect::dump(int indent) const {
	print_indent(indent);
	printf("YZRect(width=%lf, height=%lf)\n", m_width, m_height);
}
