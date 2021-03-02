#include <stdio.h>
#include "PPM.hpp"

int main() {
	PPMImage img (640, 480);

	for (size_t j = 0; j < img.height(); ++j) {
		for (size_t i = 0; i < img.width(); ++i) {
			PPMImage::RGB col = { .r = 255, .g = 127, .b = 0 };
			img.set_pixel(i, j, col);
		}
	}

	img.save("test.ppm");
}
