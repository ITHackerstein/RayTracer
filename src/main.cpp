#include <iostream>
#include <fstream>
#include <string_view>
#include "Primitives/HittableList.hpp"
#include "Primitives/Sphere.hpp"
#include "Tracer.hpp"
#include "Materials/LambertianDiffuse.hpp"
#include "Materials/Metal.hpp"

#define TOML_EXCEPTIONS 0
#include <toml++/toml.h>

static Vec3 parse_vector_array(toml::array* vector_array) {
	Vec3 v(
		*(vector_array->get(0)->value<double>()),
		*(vector_array->get(1)->value<double>()),
		*(vector_array->get(2)->value<double>())
	);

	return v;
}

static std::shared_ptr<Material> parse_material(toml::table* table) {
	auto material_type = *(table->get("type")->value<std::string_view>());
	if (material_type == "LambertianDiffuse") {
		Vec3 albedo = parse_vector_array(table->get("albedo")->as_array());
		return std::make_shared<LambertianDiffuse>(albedo);
	}

	if (material_type == "Metal") {
		Vec3 albedo = parse_vector_array(table->get("albedo")->as_array());
		double fuzzyness = *(table->get("fuzzyness")->value<double>());
		return std::make_shared<Metal>(albedo, fuzzyness);
	}

	return nullptr;
}

static std::shared_ptr<Hittable> parse_hittable_object(toml::table* table) {
	auto object_type = *(table->get("type")->value<std::string_view>());
	if (object_type == "Sphere") {
		Vec3 center = parse_vector_array(table->get("center")->as_array());
		double radius = *(table->get("radius")->value<double>());
		auto material = parse_material(table->get("material")->as_table());

		return std::make_shared<Sphere>(center, radius, material);
	}

	return nullptr;
}

int main() {
	auto res = toml::parse_file("../scene.toml");
	if (!res) {
		std::cerr << "[TOML] Error while parsing scene file!\n  " << res.error() << "\n";
		return 1;
	}

	auto table = res.table();
	std::cout << "Rendering scene: " << *(table["scene_title"].value<std::string_view>()) << "\n";

	size_t width = *(table["width"].value<size_t>());
	size_t height = *(table["height"].value<size_t>());
	size_t samples = *(table["samples"].value<size_t>());

	Vec3 camera = parse_vector_array(table["camera"].as_array());

	HittableList scene;

	auto objects_array = table["objects"].as_array();
	for (auto& object_node: *objects_array) {
		auto object = object_node.as_table();
		scene.add(parse_hittable_object(object));
	}

	Tracer t (width, height, samples, camera, scene);
	t.render();

	return 0;
}
