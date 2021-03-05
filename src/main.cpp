#include <stdio.h>
#include "Primitives/HittableList.hpp"
#include "Primitives/Sphere.hpp"
#include "Tracer.hpp"
#include "Materials/LambertianDiffuse.hpp"

int main() {
	HittableList scene;
	scene.add(std::make_shared<Sphere>(Vec3(0, 0, -4), 0.5, std::make_shared<LambertianDiffuse>(Vec3(0.8, 0.3, 0.2))));
	scene.add(std::make_shared<Sphere>(Vec3(0, -100.5, -4), 100, std::make_shared<LambertianDiffuse>(Vec3(0.3, 0.3, 0.3))));

	Vec3 camera (0, 0, 0);
	Tracer t (640, 480, 50, camera, scene);
	t.render();
}
