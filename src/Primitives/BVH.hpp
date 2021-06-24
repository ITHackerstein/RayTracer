#pragma once

#include "Hittable.hpp"
#include "AABB.hpp"

class BVH {
	public:
		BVH(const std::vector<std::shared_ptr<Hittable>>& primitives);

		bool intersects_ray(const Ray&, HitRecord&, const std::vector<std::shared_ptr<Hittable>>& primitives) const;
	private:
		struct Node {
			AABB bbox;
			size_t firstChildIndex;
			size_t primitivesCount;
			bool isLeaf;

			void make_leaf(size_t _firstChildIndex, size_t _primitiveCount) {
				primitivesCount = _primitiveCount;
				firstChildIndex = _firstChildIndex;
				isLeaf = true;
			}
		};

		struct Bin {
			AABB bbox;
			size_t primitivesCount;
			double cost;
		};

		static constexpr int MAX_DEPTH = 64;
		static constexpr size_t MAX_LEAF_SIZE = 16;
		static constexpr double TRAVERSAL_COST = 1.5;
		static constexpr size_t BIN_COUNT = 32;

		static size_t compute_bin_index_for_node(const Node&, const Vec3& center, size_t axis);

		void build_recursive(size_t nodeIndex, const std::vector<AABB>& bboxes, const std::vector<Vec3>& centers, size_t low, size_t high, int depth = MAX_DEPTH);
		size_t partition_primitive_indices(const Node&, const std::vector<Vec3>& centers, size_t axis, size_t bin, size_t low, size_t high);
		bool intersects_leaf(const Ray&, HitRecord&, const Node&, const std::vector<std::shared_ptr<Hittable>>& primitives) const;

		std::vector<Node> m_nodes;
		std::vector<size_t> m_primitiveIndices;
		size_t m_nodeCount { 0 };
};
