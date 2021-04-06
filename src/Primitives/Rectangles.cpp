#include "Rectangles.hpp"

bool XYRect::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	double t = (m_z - ray.origin().z()) / ray.direction().z();
	if (t < tMin || t > tMax)
		return false;

	double x = ray.origin().x() + t * ray.direction().x();
	if (x < m_x0 || x > m_x1)
		return false;

	double y = ray.origin().y() + t * ray.direction().y();
	if (y < m_y0 || y > m_y1)
		return false;

	record.u = (x - m_x0) / (m_x1 - m_x0);
	record.v = (y - m_y0) / (m_y1 - m_y0);

	Vec3 outNormal = Vec3(0, 0, 1);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.t = t;
	record.hitPoint = ray.at(record.t);

	return true;
}

bool XYRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(m_x0, m_y0, m_z - EPSILON), Vec3(m_x1, m_y1, m_z + EPSILON));
	return true;
}

void XYRect::dump(int indent) const {
	printf("XYRect(x0=%lf, x1=%lf, y0=%lf, y1=%lf, z=%lf)", m_x0, m_x1, m_y0, m_y1, m_z);
}

bool XZRect::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	double t = (m_y - ray.origin().y()) / ray.direction().y();
	if (t < tMin || t > tMax)
		return false;

	double x = ray.origin().x() + t * ray.direction().x();
	if (x < m_x0 || x > m_x1)
		return false;

	double z = ray.origin().z() + t * ray.direction().z();
	if (z < m_z0 || z > m_z1)
		return false;

	record.u = (x - m_x0) / (m_x1 - m_x0);
	record.v = (z - m_z0) / (m_z1 - m_z0);

	Vec3 outNormal = Vec3(0, 1, 0);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.t = t;
	record.hitPoint = ray.at(record.t);

	return true;
}

bool XZRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(m_x0, m_y - EPSILON, m_z0), Vec3(m_x1, m_y + EPSILON, m_z1));
	return true;
}

void XZRect::dump(int indent) const {
	printf("XZRect(x0=%lf, x1=%lf, y=%lf, z0=%lf, z1=%lf)", m_x0, m_x1, m_y, m_z0, m_z1);
}

bool YZRect::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	double t = (m_x - ray.origin().x()) / ray.direction().x();
	if (t < tMin || t > tMax)
		return false;

	double y = ray.origin().y() + t * ray.direction().y();
	if (y < m_y0 || y > m_y1)
		return false;

	double z = ray.origin().z() + t * ray.direction().z();
	if (z < m_z0 || z > m_z1)
		return false;

	record.u = (y - m_y0) / (m_y1 - m_y0);
	record.v = (z - m_z0) / (m_z1 - m_z0);

	Vec3 outNormal = Vec3(1, 0, 0);
	record.set_face_normal(ray, outNormal);
	record.materialPtr = m_material;

	record.t = t;
	record.hitPoint = ray.at(record.t);

	return true;
}

bool YZRect::bounding_box(AABB& bbox) const {
	bbox = AABB(Vec3(m_x - EPSILON, m_y0, m_z0), Vec3(m_x + EPSILON, m_y1, m_z1));
	return true;
}

void YZRect::dump(int indent) const {
	printf("YZRect(x=%lf, y0=%lf, y1=%lf, z0=%lf, z1=%lf)", m_x, m_y0, m_y1, m_z0, m_z1);
}
