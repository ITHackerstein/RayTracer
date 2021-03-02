#include <stdio.h>
#include "PPM.hpp"
#include "Math/Vec3.hpp"

int main() {
	PPMImage img (640, 480);

	for (size_t j = 0; j < img.height(); ++j) {
		printf("\rRow %zu / %zu", j, img.height());
		fflush(stdout);
		for (size_t i = 0; i < img.width(); ++i) {
			auto col = PPMImage::rgb_from_vector(Vec3::lerp(Vec3(0.1, 0.2, 0.8), Vec3(1, 0, 0), (double)j / img.height()));
			img.set_pixel(i, j, col);
		}
	}
	printf("\nDone!\n");

	img.save("render.ppm");
}
