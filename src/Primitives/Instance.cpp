#include "Instance.hpp"

bool Instance::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	Ray transformedRay = Transform::transform_ray(m_transform.matrixInv, ray);
	if (!m_hittableObj->intersects_ray(transformedRay, tMin, tMax, record))
		return false;

	record.hitPoint = Transform::transform_point(m_transform.matrix, record.hitPoint);
	record.normal = Transform::transform_vector(Matrix4x4::transpose(m_transform.matrixInv), record.normal);
	record.set_face_normal(transformedRay, record.normal);
	return true;
}

bool Instance::bounding_box(AABB &bbox) const {
	if (!m_hittableObj->bounding_box(bbox))
		return false;

	bbox = Transform::transform_bbox(m_transform.matrix, bbox);

	return true;
}

void Instance::dump(int indent) const {
	print_indent(indent);
	printf("Instance\n");
	m_hittableObj->dump(indent + 2);
}
