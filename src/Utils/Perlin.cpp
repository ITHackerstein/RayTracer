#include "Perlin.hpp"

Perlin::Perlin() {
	m_randomVectors = new Vec3[s_pointCount];
	for (size_t i = 0; i < s_pointCount; ++i)
		m_randomVectors[i] = Vec3::normalize(Vec3::random(-1, 1));

	m_permutationX = perlin_generate_permutations();
	m_permutationY = perlin_generate_permutations();
	m_permutationZ = perlin_generate_permutations();
}

Perlin::~Perlin() {
	delete[] m_randomVectors;
	delete[] m_permutationX;
	delete[] m_permutationY;
	delete[] m_permutationZ;
}

double Perlin::noise(const Vec3& p) const {
	double u = p.x() - floor(p.x());
	double v = p.y() - floor(p.y());
	double w = p.z() - floor(p.z());

	auto i = static_cast<int>(floor(p.x()));
	auto j = static_cast<int>(floor(p.y()));
	auto k = static_cast<int>(floor(p.z()));

	Vec3 c[2][2][2];

	for (size_t di = 0; di < 2; ++di)
		for (size_t dj = 0; dj < 2; ++dj)
			for (size_t dk = 0; dk < 2; ++dk)
				c[di][dj][dk] = m_randomVectors[m_permutationX[(i + di) & 255] ^ m_permutationY[(j + dj) & 255] ^ m_permutationZ[(k + dk) & 255]];

	return perlin_interpolation(c, u, v, w);
}

double Perlin::turb(const Vec3& p, size_t depth) const {
	double accum = 0.0;
	auto tmpP = p;
	auto weight = 1.0;

	for (size_t i = 0; i < depth; ++i) {
		accum += weight * noise(tmpP);
		weight *= 0.5;
		tmpP *= 2;
	}

	return fabs(accum);
}

int* Perlin::perlin_generate_permutations() {
	int* p = new int[s_pointCount];

	for (size_t i = 0; i < s_pointCount; ++i)
		p[i] = i;

	permute(p, s_pointCount);

	return p;
}

void Perlin::permute(int* p, size_t n) {
	for (size_t i = n - 1; i > 0; --i) {
		size_t target = static_cast<size_t>(random_int(0, i));
		std::swap(p[i], p[target]);
	}
}

double Perlin::perlin_interpolation(Vec3 c[2][2][2], double u, double v, double w) {
	double uu = u * u * (3 - 2 * u);
	double vv = v * v * (3 - 2 * v);
	double ww = w * w * (3 - 2 * w);

	double accum = 0.0;
	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			for (size_t k = 0; k < 2; ++k) {
				Vec3 weight (u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww)) * Vec3::dot(c[i][j][k], weight);
			}
		}
	}

	return accum;
}
