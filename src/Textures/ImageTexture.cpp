#include "ImageTexture.hpp"
#include "../Utils/STBImageWrapper.hpp"

ImageTexture::ImageTexture(const char* fileName) {
	int n = s_bytesPerPixel;
	m_textureData = stbi_load(fileName, &m_width, &m_height, &n, n);
	assert(m_textureData && "Couldn't load image texture!");

	m_imagePitch = m_width * n;
}

Vec3 ImageTexture::value(double u, double v, const Vec3& p) const {
	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);

	auto i = std::min(static_cast<int>(u * m_width), m_width - 1);
	auto j = std::min(static_cast<int>(v * m_height), m_height - 1);

	auto pixel = m_textureData + j * m_imagePitch + i * s_bytesPerPixel;

	return Vec3(pixel[0], pixel[1], pixel[2]) / 255.0;
}
