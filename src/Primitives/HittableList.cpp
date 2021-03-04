#include "HittableList.hpp"

bool HittableList::intersects_ray(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
	HitRecord tempRecord;
	bool hasHit = false;
	double closest = tMax;

	for (auto& obj: m_objects) {
		if (obj->intersects_ray(ray, tMin, closest, tempRecord)) {
			closest = tempRecord.t;
			record = tempRecord;
			hasHit = true;
		}
	}

	return hasHit;
}
