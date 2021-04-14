#include "Transform.hpp"

Transform Transform::new_translation_transform(Vec3 offset) {
	Matrix4x4 translationMatrix (
		1, 0, 0, offset.x(),
		0, 1, 0, offset.y(),
		0, 0, 1, offset.z(),
		0, 0, 0, 1
	);
	return Transform(Transform::Type::Translation, translationMatrix);
}

Transform Transform::new_rotationX_transform(double theta) {
	double sint = sin(theta);
	double cost = cos(theta);

	Matrix4x4 rotationXMatrix (
		1, 0, 0, 0,
		0, cost, -sint, 0,
		0, sint, cost, 0,
		0, 0, 0, 1
	);
	return Transform(Transform::Type::RotationX, rotationXMatrix);
}

Transform Transform::new_rotationY_transform(double theta) {
	double sint = sin(theta);
	double cost = cos(theta);

	Matrix4x4 rotationYMatrix (
		cost, 0, sint, 0,
		0, 1, 0, 0,
		-sint, 0, cost, 0,
		0, 0, 0, 1
	);
	return Transform(Transform::Type::RotationY, rotationYMatrix);
}

Transform Transform::new_rotationZ_transform(double theta) {
	double sint = sin(theta);
	double cost = cos(theta);

	Matrix4x4 rotationZMatrix (
		cost, -sint, 0, 0,
		sint, cost, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	return Transform(Transform::Type::RotationZ, rotationZMatrix);
}

Transform Transform::new_scale_transform(Vec3 scale) {
	Matrix4x4 scaleMatrix (
		scale.x(), 0, 0, 0,
		0, scale.y(), 0, 0,
		0, 0, scale.z(), 0,
		0, 0, 0, 1
	);

	return Transform(Transform::Type::Scale, scaleMatrix);
}

Vec3 Transform::transform_point(const Matrix4x4& m, const Vec3& p) {
	return Vec3(
		m(0, 0) * p.x() + m(0, 1) * p.y() + m(0, 2) * p.z() + m(0, 3),
		m(1, 0) * p.x() + m(1, 1) * p.y() + m(1, 2) * p.z() + m(1, 3),
		m(2, 0) * p.x() + m(2, 1) * p.y() + m(2, 2) * p.z() + m(2, 3)
	);
}

Vec3 Transform::transform_vector(const Matrix4x4& m, const Vec3& v) {
	return Vec3(
		m(0, 0) * v.x() + m(0, 1) * v.y() + m(0, 2) * v.z(),
		m(1, 0) * v.x() + m(1, 1) * v.y() + m(1, 2) * v.z(),
		m(2, 0) * v.x() + m(2, 1) * v.y() + m(2, 2) * v.z()
	);
}

Ray Transform::transform_ray(const Matrix4x4& m, const Ray& ray) {
	return Ray(transform_point(m, ray.origin()), transform_vector(m, ray.direction()));
}

AABB Transform::transform_bbox(const Matrix4x4& m, const AABB& bbox) {
	Matrix4x4 absoluteMtx = Matrix4x4::absolute(m);
	Vec3 bboxCenter = transform_point(absoluteMtx, (bbox.minimum() + bbox.maximum()) / 2);
	Vec3 bboxHalfDiag = transform_vector(absoluteMtx, (bbox.maximum() - bbox.minimum()) / 2);

	return AABB(bboxCenter - bboxHalfDiag, bboxCenter + bboxHalfDiag);
}
