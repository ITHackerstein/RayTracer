#pragma once

#include "../Math/Vec3.hpp"
#include "Random.hpp"

class Perlin {
	public:
		Perlin();
		~Perlin();

		double noise(const Vec3& p) const;
		double turb(const Vec3& p, size_t depth=7) const;

	private:
		static constexpr size_t s_pointCount = 256;
		Vec3* m_randomVectors;
		int* m_permutationX;
		int* m_permutationY;
		int* m_permutationZ;

		static int* perlin_generate_permutations();
		static void permute(int* p, size_t n);
		static double perlin_interpolation(Vec3 c[2][2][2], double u, double v, double w);
};
