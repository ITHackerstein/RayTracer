#include "HittableList.hpp"

bool HittableList::intersects_ray(const Ray& ray, HitRecord& record) const {
	bool hasHit = false;

	for (auto& obj: m_objects) {
		if (obj->intersects_ray(ray, record))
			hasHit = true;
	}

	return hasHit;
}

bool HittableList::bounding_box(AABB& bbox) const {
	if (m_objects.empty()) return false;

	AABB temp;
	bool firstBox = true;

	for (const auto& obj: m_objects) {
		if (!obj->bounding_box(temp)) return false;

		bbox = firstBox ? temp : AABB::surrounding_box(bbox, temp);
		firstBox = false;
	}

	return true;
}

void HittableList::dump(int indent) const {
	print_indent(indent);
	printf("HittableList:\n");
	print_indent(indent + 1);
	printf("Objects:\n");
	for (const auto& obj: m_objects) {
		obj->dump(indent + 2);
	}
}
