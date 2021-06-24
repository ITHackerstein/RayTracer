#include "BVH.hpp"

#include <utility>

size_t BVH::compute_bin_index_for_node(const Node& node, const Vec3& center, size_t axis) {
	double min = node.bbox.minimum()[axis];
	double max = node.bbox.maximum()[axis];

	double centerToBin = BIN_COUNT / (max - min);
	double floatIndex = (center[axis] - min) * centerToBin;
	size_t binIndex = floatIndex < 0 ? 0 : (size_t) floatIndex;
	return binIndex >= BIN_COUNT ? BIN_COUNT - 1 : binIndex;
}

BVH::BVH(const std::vector<std::shared_ptr<Hittable>>& primitives) {
	size_t primitivesCount = primitives.size();
	if (primitivesCount >= 1) {
		m_primitiveIndices.resize(primitivesCount);

		std::vector<Vec3> centers;
		centers.resize(primitivesCount);

		std::vector<AABB> bboxes;
		bboxes.resize(primitivesCount);

		AABB rootBBox = AABB::empty();
		for (size_t i = 0; i < primitivesCount; ++i) {
			m_primitiveIndices[i] = i;
			assert(primitives[i]->center(centers[i]));
			assert(primitives[i]->bounding_box(bboxes[i]));
			rootBBox = AABB::surrounding_box(rootBBox, bboxes[i]);
		}

		// std::cout << "Centers: \n";
		// for (const auto& center: centers)
		// 	std::cout << "  " << center << '\n';

		// std::cout << "BBoxes: \n";
		// for (const auto& bbox: bboxes)
		// 	std::cout << "  min: " << bbox.minimum() << ", max: " << bbox.maximum() << '\n';

		size_t maxNodes = 2 * primitivesCount - 1;

		m_nodeCount = 1;
		m_nodes.resize(maxNodes);
		m_nodes[0].bbox = rootBBox;

		build_recursive(0, bboxes, centers, 0, primitivesCount);

		m_nodes.resize(m_nodeCount);
		// std::cout << m_nodeCount << '\n';

		// for (size_t i = 0; i < m_nodeCount; ++i) {
		// 	std::cout << "Node " << i << '\n';
		// 	std::cout << "  bbox: [ min: " << m_nodes[i].bbox.minimum() << ", " << "max: " << m_nodes[i].bbox.maximum() << "]\n";
		// 	std::cout << "  firstChildIndex: " << m_nodes[i].firstChildIndex << '\n';
		// 	std::cout << "  primitivesCount: " << m_nodes[i].primitivesCount << '\n';
		// 	std::cout << "  isLeaf: " << m_nodes[i].isLeaf << '\n';
		// }
	}
}

void BVH::build_recursive(size_t nodeIndex, const std::vector<AABB>& bboxes, const std::vector<Vec3>& centers, size_t low, size_t high, int depth) {
	size_t primitivesCount = high - low;

	if (depth <= 0 || primitivesCount < 2) {
		m_nodes[nodeIndex].make_leaf(low, primitivesCount);
		return;
	}

	Node& node = m_nodes[nodeIndex];

	Bin bins[3][BIN_COUNT];
	double minCost[3] = { INF_DOUBLE, INF_DOUBLE, INF_DOUBLE };
	size_t minBin[3] = { 1, 1, 1 };
	for (size_t axis = 0; axis < 3; ++axis) {
		for (size_t i = 0; i < BIN_COUNT; ++i) {
			bins[axis][i].bbox = AABB::empty();
			bins[axis][i].primitivesCount = 0;
		}

		for (size_t i = low; i < high; ++i) {
			size_t primitiveIndex = m_primitiveIndices[i];
			size_t binIndex = compute_bin_index_for_node(node, centers[primitiveIndex], axis);
			Bin& bin = bins[axis][binIndex];
			bin.bbox = AABB::surrounding_box(bin.bbox, bboxes[primitiveIndex]);
			++bin.primitivesCount;
		}

		AABB curBBox = AABB::empty();
		size_t curCount = 0;
		for (size_t i = BIN_COUNT; i > 1; --i) {
			Bin& bin = bins[axis][i - 1];
			curCount += bin.primitivesCount;
			curBBox = AABB::surrounding_box(curBBox, bin.bbox);
			bin.cost = curCount * curBBox.area();
		}

		curBBox = AABB::empty();
		curCount = 0;
		for (size_t i = 0; i < BIN_COUNT - 1; ++i) {
			Bin& bin = bins[axis][i];
			curCount += bin.primitivesCount;
			curBBox = AABB::surrounding_box(curBBox, bin.bbox);
			double cost = curCount * curBBox.area() + bins[axis][i + 1].cost;
			if (cost < minCost[axis]) {
				minBin[axis] = i + 1;
				minCost[axis] = cost;
			}
		}
	}

	size_t minAxis = 0;
	if (minCost[1] < minCost[0]) minAxis = 1;
	if (minCost[2] < minCost[minAxis]) minAxis = 2;

	double leafCost = node.bbox.area() * (primitivesCount - TRAVERSAL_COST);
	if (minCost[minAxis] > leafCost) {
		if (primitivesCount > MAX_LEAF_SIZE) {
			for (size_t i = 0, accumCount = 0, bestApprox = primitivesCount; i < BIN_COUNT - 1; ++i) {
				accumCount += bins[minAxis][i].primitivesCount;
				size_t approx = abs((int) primitivesCount / 2 - (int) accumCount);
				if (approx < bestApprox) {
					bestApprox = approx;
					minBin[minAxis] = i + 1;
				}
			}
		} else {
			node.make_leaf(low, primitivesCount);
			return;
		}
	}

	size_t lowRight = partition_primitive_indices(node, centers, minAxis, minBin[minAxis], low, high);
	if (lowRight > low) {
		size_t leftIndex = m_nodeCount;
		size_t rightIndex = leftIndex + 1;
		m_nodeCount += 2;

		AABB leftBBox = AABB::empty();
		AABB rightBBox = AABB::empty();
		for (size_t i = 0; i < minBin[minAxis]; ++i)
			leftBBox = AABB::surrounding_box(leftBBox, bins[minAxis][i].bbox);
		for (size_t i = minBin[minAxis]; i < BIN_COUNT; ++i)
			rightBBox = AABB::surrounding_box(rightBBox, bins[minAxis][i].bbox);
		m_nodes[leftIndex].bbox = leftBBox;
		m_nodes[rightIndex].bbox = rightBBox;
		node.firstChildIndex = leftIndex;
		node.isLeaf = false;

		build_recursive(leftIndex, bboxes, centers, low, lowRight, depth - 1);
		build_recursive(rightIndex, bboxes, centers, lowRight, high, depth - 1);
	} else {
		node.make_leaf(low, primitivesCount);
	}
}

size_t BVH::partition_primitive_indices(const Node& node, const std::vector<Vec3>& centers, size_t axis, size_t bin, size_t low, size_t high) {
	size_t i = low;
	size_t j = high;
	while (i < j) {
		while (i < j) {
			size_t binIndex = compute_bin_index_for_node(node, centers[m_primitiveIndices[i]], axis);
			if (binIndex >= bin)
				break;
			++i;
		}

		while (i < j) {
			size_t binIndex = compute_bin_index_for_node(node, centers[m_primitiveIndices[j - 1]], axis);
			if (binIndex < bin)
				break;
			--j;
		}

		if (i >= j)
			break;

		std::swap(m_primitiveIndices[i], m_primitiveIndices[j - 1]);

		--j;
		++i;
	}

	return i;
}

bool BVH::intersects_ray(const Ray& ray, HitRecord& record, const std::vector<std::shared_ptr<Hittable> > &primitives) const {
	if (m_nodeCount < 1)
		return false;

	double maxDist = record.distance;

	std::vector<size_t> stack;
	if (m_nodeCount == 1) {
		if (m_nodes[0].bbox.intersects_ray(ray, maxDist))
			return intersects_leaf(ray, record, m_nodes[0], primitives);
		return false;
	}

	size_t nodeIndex = 0;
	bool hasHit = false;
	while (true) {
		// std::cout << "nodeIndex: " << nodeIndex << '\n';
		size_t firstChildIndex = m_nodes[nodeIndex].firstChildIndex;
		// std::cout << "firstChildIndex: " << firstChildIndex << '\n';
		size_t leftNodeIndex = firstChildIndex;
		size_t rightNodeIndex = firstChildIndex + 1;

		double tLeft;
		double tRight;
		bool hasHitLeft = m_nodes[leftNodeIndex].bbox.intersects_ray(ray, maxDist, tLeft);
		bool hasHitRight = m_nodes[rightNodeIndex].bbox.intersects_ray(ray, maxDist, tRight);
		// std::cout << "hasHitLeft: " << hasHitLeft << ", hasHitRight: " << hasHitRight << '\n';

		if (hasHitLeft) {
			if (m_nodes[leftNodeIndex].isLeaf) {
				// std::cout << "Left node is leaf\n";
				if (intersects_leaf(ray, record, m_nodes[leftNodeIndex], primitives)) {
					// std::cout << "Left node hits ray\n";
					maxDist = record.distance;
					hasHit = true;
				}
				leftNodeIndex = m_nodeCount;
			}
		} else
			leftNodeIndex = m_nodeCount;

		if (hasHitRight) {
			if (m_nodes[rightNodeIndex].isLeaf) {
				// std::cout << "Right node is leaf\n";
				if (intersects_leaf(ray, record, m_nodes[rightNodeIndex], primitives)) {
					// std::cout << "Right node hits ray\n";
					maxDist = record.distance;
					hasHit = true;
				}
				rightNodeIndex = m_nodeCount;
			}
		} else
			rightNodeIndex = m_nodeCount;

		if (leftNodeIndex != m_nodeCount && rightNodeIndex != m_nodeCount) {
			if (tLeft > tRight)
				std::swap(leftNodeIndex, rightNodeIndex);
			nodeIndex = leftNodeIndex;
			stack.push_back(rightNodeIndex);
		} else if ((leftNodeIndex != m_nodeCount) ^ (rightNodeIndex != m_nodeCount)) {
			nodeIndex = rightNodeIndex != m_nodeCount ? rightNodeIndex : leftNodeIndex;
		} else {
			if (stack.empty())
				break;

			nodeIndex = stack.back();
			stack.pop_back();
		}
	}

	return hasHit;
}

bool BVH::intersects_leaf(const Ray& ray, HitRecord& record, const Node& node, const std::vector<std::shared_ptr<Hittable>>& primitives) const {
	// std::cout << "intersects_leaf: primitives " << primitives.size() << '\n';
	bool hasHit = false;

	for (size_t i = 0; i < node.primitivesCount; ++i) {
		if (primitives[m_primitiveIndices[node.firstChildIndex + i]]->intersects_ray(ray, record))
			hasHit = true;
	}

	return hasHit;
}
