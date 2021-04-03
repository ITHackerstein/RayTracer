#pragma once

#include <random>
#include <PCG/pcg_random.hpp>

static pcg_extras::seed_seq_from<std::random_device> seed;
static pcg64 rng(seed);
static std::uniform_real_distribution<double> distr(0.0, 1.0);

inline double random_double() {
	return distr(rng);
}

inline double random_double(double min, double max) {
	return random_double() * (max - min) + min;
}

inline int random_int(int min, int max) {
	return static_cast<int>(random_double(min, max + 1));
}
