#include "BVH.hpp"

static inline bool box_cmp(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis) {
	AABB aBBox;
	AABB bBBox;
	assert((a->bounding_box(aBBox) && b->bounding_box(bBBox)) && "No bounding box in costruncting BVH!");

	return aBBox.minimum()[axis] < bBBox.minimum()[axis];
}

static inline bool box_cmp_x(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
	return box_cmp(a, b, 0);
}

static inline bool box_cmp_y(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
	return box_cmp(a, b, 1);
}

static inline bool box_cmp_z(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b) {
	return box_cmp(a, b, 2);
}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& objects, size_t low, size_t high) {
	auto objectsCopy = objects;

	int axis = random_int(0, 2);
	auto axisCmp = axis == 0 ? box_cmp_x : (axis == 1 ? box_cmp_y : box_cmp_z);

	size_t objectsSize = high - low;

	if (objectsSize == 1) {
		m_left = m_right = objectsCopy[low];
	} else if (objectsSize == 2) {
		if (axisCmp(objectsCopy[low], objectsCopy[low + 1])) {
			m_left = objectsCopy[low];
			m_right = objectsCopy[low + 1];
		} else {
			m_left = objectsCopy[low + 1];
			m_right = objectsCopy[low];
		}
	} else {
		std::sort(objectsCopy.begin() + low, objectsCopy.begin() + high, axisCmp);

		size_t mid = low + objectsSize / 2;
		m_left = std::make_shared<BVHNode>(objectsCopy, low, mid);
		m_right = std::make_shared<BVHNode>(objectsCopy, mid, high);
	}

	AABB leftBBox;
	AABB rightBBox;
	assert((m_left->bounding_box(leftBBox) && m_right->bounding_box(rightBBox)) && "No bounding box in costruncting BVH!");

	m_bbox = AABB::surrounding_box(leftBBox, rightBBox);
}

bool BVHNode::intersects_ray(const Ray& ray, HitRecord& record) const {
	if (!m_bbox.intersects_ray(ray, record.distance))
		return false;

	bool hasHitLeft = m_left->intersects_ray(ray, record);
	bool hasHitRight = m_right->intersects_ray(ray, record);

	return hasHitLeft || hasHitRight;
}

bool BVHNode::bounding_box(AABB& bbox) const {
	bbox = m_bbox;
	return true;
}

void BVHNode::dump(int indent) const {
	print_indent(indent);
	printf("BVHNode:\n");

	print_indent(indent + 1);
	printf("Left:\n");
	m_left->dump(indent + 2);

	print_indent(indent + 1);
	printf("Right:\n");
	m_right->dump(indent + 2);
}
