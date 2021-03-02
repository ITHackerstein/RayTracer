#pragma once

#include <new>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Math/Vec3.hpp"

class PPMImage {
	public:
		struct RGB {
			uint8_t r { 0 };
			uint8_t g { 0 };
			uint8_t b { 0 };
		};

		PPMImage(size_t width, size_t height);
		~PPMImage() { delete[] m_pixelBuffer; }

		size_t width() const { return m_width; }
		size_t height() const { return m_height; }

		int set_pixel(size_t x, size_t y, RGB);
		int get_pixel(size_t x, size_t y, RGB&) const;

		int save(const char* fileName) const;

		static RGB rgb_from_vector(Vec3 v);

	private:
		inline size_t pb_idx(size_t x, size_t y) const { return y * m_width + x; }

		size_t m_width  { 0 };
		size_t m_height { 0 };
		RGB* m_pixelBuffer;
};
