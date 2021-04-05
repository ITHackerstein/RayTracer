#include "SceneParser.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <scene-file>\n", argv[0]);
		return 1;
	}

	SceneParser sceneParser(argv[1]);
	auto outputImageOptions = sceneParser.parse_output_image_options();
	auto camera = sceneParser.parse_camera();
	auto backgroundColor = sceneParser.parse_background_color();
	auto objects = sceneParser.parse_objects();

	Tracer t (outputImageOptions, camera, backgroundColor, objects);
	t.render();

	return 0;
}
