#include "Mesh.hpp"

bool Mesh::intersects_ray(const Ray& ray, HitRecord& record) const {
	if (!m_facesBVH.intersects_ray(ray, record, m_faces))
		return false;

	record.materialPtr = m_materialPtr;
	return true;
}

bool Mesh::center(Vec3& center) const {
	AABB bbox;
	if (!bounding_box(bbox))
		return false;

	center = (bbox.minimum() + bbox.maximum()) / 2;
	return true;
}

bool Mesh::bounding_box(AABB& bbox) const {
	bbox = m_facesBVH.bounding_box();
	return true;
}

void Mesh::dump(int indent) const {
}
