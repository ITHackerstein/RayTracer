#include "PPM.hpp"

PPMImage::PPMImage(size_t width, size_t height):
	m_width(width), m_height(height), m_pixelBuffer(new PPMImage::RGB[width * height])
{}

int PPMImage::set_pixel(size_t x, size_t y, PPMImage::RGB color) {
	if (x >= m_width || y >= m_height) return -1;

	m_pixelBuffer[pb_idx(x, y)] = color;
	return 0;
}

int PPMImage::get_pixel(size_t x, size_t y, PPMImage::RGB& color) const {
	if (x >= m_width || y >= m_height) return -1;

	color = m_pixelBuffer[pb_idx(x, y)];
	return 0;
}

int PPMImage::save(const char* fileName) const {
	FILE *fp = fopen(fileName, "wb");
	if (fp == NULL) return -1;

	fprintf(fp, "P6 %zu %zu 255\n", width(), height());

	for (size_t j = 0; j < height(); ++j) {
		for (size_t i = 0; i < width(); ++i) {
			fputc(m_pixelBuffer[pb_idx(i, j)].r, fp);
			fputc(m_pixelBuffer[pb_idx(i, j)].g, fp);
			fputc(m_pixelBuffer[pb_idx(i, j)].b, fp);
		}
	}

	fclose(fp);
	return 0;
}
