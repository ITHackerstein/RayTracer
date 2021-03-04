#include <stdio.h>
#include "Primitives/HittableList.hpp"
#include "Primitives/Sphere.hpp"
#include "Tracer.hpp"

int main() {
	HittableList scene;
	scene.add(std::make_shared<Sphere>(Vec3(0, 0, -3), 0.5));
	scene.add(std::make_shared<Sphere>(Vec3(0, -100.5, -3), 100));

	Tracer t (640, 480, scene);
	t.render();
}
