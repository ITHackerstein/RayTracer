#define TOML_EXCEPTIONS 0

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string_view>
#include <toml++/toml.h>

#include "Materials/LambertianDiffuse.hpp"
#include "Materials/Metal.hpp"
#include "Materials/Dielectric.hpp"
#include "Primitives/HittableList.hpp"
#include "Primitives/Sphere.hpp"
#include "Tracer.hpp"

static toml::node* get_key_or_error(toml::table& table, const char* key) {
	auto node = table.get(key);
	if (node)
		return node;

	std::cerr << "[TOML] Key '" << key << "' not found\n";
	exit(1);
}

template<typename T>
static T get_variable_or_error(toml::table& table, const char* variableName) {
	auto variable = get_key_or_error(table, variableName)->value<T>();
	if (variable)
		return *variable;

	std::cerr << "[TOML] Variable '" << variableName << "' not found!\n";
	exit(1);
}

static toml::array get_array_or_error(toml::table& table, const char* arrayName) {
	auto arr = get_key_or_error(table, arrayName)->as_array();
	if (arr)
		return *arr;

	std::cerr << "[TOML] Array '" << arrayName << "' not found!\n";
	exit(1);
}

static toml::table get_table_or_error(toml::table& table, const char *tableName) {
	auto childTable = get_key_or_error(table, tableName)->as_table();
	if (childTable)
		return *childTable;

	std::cerr << "[TOML] Table '" << tableName << "' not found!\n";
	exit(1);
}

static Vec3 parse_vector_array(toml::array& vectorArray) {
	if (vectorArray.size() < 3) {
		std::cerr << "[TOML] Invalid vector array!\n";
		exit(1);
	}

	auto x = vectorArray.get(0)->value<double>();
	auto y = vectorArray.get(1)->value<double>();
	auto z = vectorArray.get(2)->value<double>();
	if (!x || !y || !z) {
		std::cerr << "[TOML] Invalid vector array!\n";
		exit(1);
	}

	return Vec3(*x, *y, *z);
}

static std::shared_ptr<Material> parse_material(toml::table& table) {
	auto materialType = get_variable_or_error<std::string_view>(table, "type");
	if (materialType == "LambertianDiffuse") {
		auto albedoArray = get_array_or_error(table, "albedo");
		Vec3 albedo = parse_vector_array(albedoArray);

		return std::make_shared<LambertianDiffuse>(albedo);
	}

	if (materialType == "Metal") {
		auto albedoArray = get_array_or_error(table, "albedo");
		Vec3 albedo = parse_vector_array(albedoArray);

		double fuzzyness = get_variable_or_error<double>(table, "fuzzyness");

		return std::make_shared<Metal>(albedo, fuzzyness);
	}

	if (materialType == "Dielectric") {
		double refractiveIndex = get_variable_or_error<double>(table, "refractiveIndex");

		return std::make_shared<Dielectric>(refractiveIndex);
	}

	return nullptr;
}

static std::shared_ptr<Hittable> parse_hittable_object(toml::table& table) {
	auto objectType = get_variable_or_error<std::string_view>(table, "type");
	if (objectType == "Sphere") {
		auto centerArray = get_array_or_error(table, "center");
		Vec3 center = parse_vector_array(centerArray);

		double radius = get_variable_or_error<double>(table, "radius");

		auto materialTable = get_table_or_error(table, "material");
		auto material = parse_material(materialTable);
		if (!material) {
			std::cerr << "[RayTracer] Invalid material!\n";
			exit(1);
		}

		return std::make_shared<Sphere>(center, radius, material);
	}

	return nullptr;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <scene-file>\n";
		return 1;
	}

	char* fileName = argv[1];

	auto res = toml::parse_file(fileName);
	if (!res) {
		std::cerr << "[TOML] Error while parsing scene file!\n  " << res.error() << "\n";
		return 1;
	}

	auto table = res.table();

	auto sceneTitle = get_variable_or_error<std::string_view>(table, "scene_title");
	auto width = get_variable_or_error<size_t>(table, "width");
	auto height = get_variable_or_error<size_t>(table, "height");
	auto samples = get_variable_or_error<size_t>(table, "samples");

	auto cameraArray = get_array_or_error(table, "camera");
	Vec3 camera = parse_vector_array(cameraArray);

	HittableList scene;

	auto objectsArray = get_array_or_error(table, "objects");
	for (auto& objectNode: objectsArray) {
		auto object = objectNode.as_table();
		if (!object) {
			std::cerr << "[TOML] Invalid object!\n";
			exit(1);
		}

		auto hittableObject = parse_hittable_object(*object);
		if (!hittableObject) {
			std::cerr << "[RayTracer] Invalid object!\n";
			exit(1);
		}

		scene.add(parse_hittable_object(*object));
	}

	std::cout << "[RayTracer] Rendering scene:\n";
	std::cout << "  Title: " << sceneTitle << "\n";
	std::cout << "  Width: " << width << "\n";
	std::cout << "  Height: " << height << "\n";
	std::cout << "  Samples per pixel: " << samples << "\n";
	std::cout << "  Camera: [ " << camera.x << ", " << camera.y << ", " << camera.z << " ]\n";
	std::cout << "  " << scene.size() << " objects\n";

	Tracer t (width, height, samples, camera, scene);
	t.render();

	return 0;
}
