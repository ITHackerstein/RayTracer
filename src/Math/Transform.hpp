#pragma once

#include "../Math/Matrix4x4.hpp"
#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "../Primitives/AABB.hpp"

struct Transform {
	enum class Type {
		Identity,
		Translation,
		RotationX,
		RotationY,
		RotationZ,
		Scale,
		Composite
	} type;
	Matrix4x4 matrix;
	Matrix4x4 matrixInv;

	Transform():
		Transform(Type::Identity, Matrix4x4::identity()) {}

	Transform(Type t, Matrix4x4 m):
		type(t), matrix(m), matrixInv(Matrix4x4::inverse(m)) {}

	static Transform new_translation_transform(Vec3 offset);
	static Transform new_rotationX_transform(double theta);
	static Transform new_rotationY_transform(double theta);
	static Transform new_rotationZ_transform(double theta);
	static Transform new_scale_transform(Vec3 scale);

	static Vec3 transform_point(const Matrix4x4&, const Vec3&);
	static Vec3 transform_vector(const Matrix4x4&, const Vec3&);
	static Ray transform_ray(const Matrix4x4&, const Ray&);
	static AABB transform_bbox(const Matrix4x4&, const AABB&);
};
