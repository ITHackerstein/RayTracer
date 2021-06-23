#pragma once

#include "../Math/Vec3.hpp"
#include "../Math/Ray.hpp"
#include "../Utils/Math.hpp"
#include <memory>

class Material; // Forward declaration of Material

struct HitRecord {
	Vec3 hitPoint;
	Vec3 normal;
	std::shared_ptr<Material> materialPtr;
	double distance { INF_DOUBLE };
	double u;
	double v;
	bool isOut;

	// This determines whether the normal points outside or inside the object.
	inline void set_face_normal(const Ray& ray, const Vec3& outNormal) {
		isOut = Vec3::dot(ray.direction(), outNormal) < 0.0;
		normal = isOut ? outNormal : -outNormal;
	}
};
