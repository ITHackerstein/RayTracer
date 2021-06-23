#include "Triangle.hpp"

bool Triangle::intersects_ray(const Ray& ray, HitRecord& record) const {
	// Möller-Trumbore ray-triangle intersection
	Vec3 e1 = m_v0 - m_v1;
	Vec3 e2 = m_v2 - m_v0;
	Vec3 n = Vec3::cross(e1, e2);

	Vec3 c = m_v0 - ray.origin();
	Vec3 r = Vec3::cross(ray.direction(), c);
	double invDet = 1.0 / Vec3::dot(n, ray.direction());

	double u = Vec3::dot(r, e2) * invDet;
	double v = Vec3::dot(r, e1) * invDet;
	double w = 1.0 - u - v;

	if (u >= 0 && v >= 0 && u + v <= 1) {
		double t = Vec3::dot(n, c) * invDet;
		if (t > EPSILON && t < record.distance) {
			record.u = u; record.v = v;
			record.distance = t;

			if (m_hasNormals) {
				record.normal = u * m_n0 + v * m_n1 + w * m_n2;
			} else {
				record.normal = n;
			}

			record.set_face_normal(ray, record.normal);

			record.hitPoint = ray.at(t);
			record.materialPtr = m_materialPtr;
			return true;
		}
	}

	return false;
}

bool Triangle::bounding_box(AABB &bbox) const {
	double minX = std::min(std::min(m_v0.x(), m_v1.x()), m_v2.x());
	double minY = std::min(std::min(m_v0.y(), m_v1.y()), m_v2.y());
	double minZ = std::min(std::min(m_v0.z(), m_v1.z()), m_v2.z());

	double maxX = std::max(std::max(m_v0.x(), m_v1.x()), m_v2.x());
	double maxY = std::max(std::max(m_v0.y(), m_v1.y()), m_v2.y());
	double maxZ = std::max(std::max(m_v0.z(), m_v1.z()), m_v2.z());

	bbox = AABB(Vec3(minX, minY, minZ), Vec3(maxX, maxY, maxZ));
	return true;
}

void Triangle::dump(int indent) const {
	print_indent(indent);
	printf("Triangle(v0=[ %f %f %f ], v1=[ %f %f %f ], v2=[ %f %f %f ])\n",
		m_v0.x(), m_v0.y(), m_v0.z(),
		m_v1.x(), m_v1.y(), m_v1.z(),
		m_v2.x(), m_v2.y(), m_v2.z()
	);
}
