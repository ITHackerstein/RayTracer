#pragma once

#include <stdint.h>
#include "../Utils/Math.hpp"
#include "Texture.hpp"

class ImageTexture : public Texture {
	public:
		const static int s_bytesPerPixel = 3;

		ImageTexture():
			m_textureData(nullptr), m_width(0), m_height(0), m_imagePitch(0) {}

		ImageTexture(const char* fileName);
		~ImageTexture() { delete m_textureData; }

		virtual Vec3 value(double u, double v, const Vec3 &p) const override;

	private:
		uint8_t* m_textureData;
		int m_width;
		int m_height;
		int m_imagePitch;
};
