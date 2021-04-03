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
#include "Primitives/BVH.hpp"
#include "Primitives/Sphere.hpp"
#include "Textures/CheckerTexture.hpp"
#include "Textures/SolidColor.hpp"
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

static Camera parse_camera_table(toml::table& table, double aspectRatio) {
	auto positionArray = get_array_or_error(table, "position");
	Vec3 position = parse_vector_array(positionArray);

	auto lookAtArray = get_array_or_error(table, "look_at");
	Vec3 lookAt = parse_vector_array(lookAtArray);

	auto fov = degrees_to_radians(get_variable_or_error<double>(table, "fov"));

	auto lensAperture = get_variable_or_error<double>(table, "lens_aperture");

	auto focusDist = get_variable_or_error<double>(table, "focus_distance");
	if (focusDist < 0)
		focusDist = (position - lookAt).mag();

	return Camera(position, lookAt, fov, aspectRatio, lensAperture, focusDist);
}

static std::shared_ptr<Texture> parse_texture(toml::table& textureObject) {
	auto textureType = get_variable_or_error<std::string_view>(textureObject, "type");
	if (textureType == "SolidColor") {
		auto colorArray = get_array_or_error(textureObject, "color");
		Vec3 color = parse_vector_array(colorArray);

		return std::make_shared<SolidColor>(color);
	} else if (textureType == "CheckerTexture") {
		auto t1Object = get_table_or_error(textureObject, "odd");
		std::shared_ptr<Texture> t1 = parse_texture(t1Object);
		auto t2Object = get_table_or_error(textureObject, "even");
		std::shared_ptr<Texture> t2 = parse_texture(t2Object);

		return std::make_shared<CheckerTexture>(t1, t2);
	}

	return nullptr;
}

static std::shared_ptr<Material> parse_material(toml::table& table) {
	auto materialType = get_variable_or_error<std::string_view>(table, "type");
	if (materialType == "LambertianDiffuse") {
		auto textureObject = get_table_or_error(table, "albedo");
		std::shared_ptr<Texture> texture = parse_texture(textureObject);

		return std::make_shared<LambertianDiffuse>(texture);
	}

	if (materialType == "Metal") {
		auto albedoArray = get_array_or_error(table, "albedo");
		Vec3 albedo = parse_vector_array(albedoArray);

		double fuzzyness = get_variable_or_error<double>(table, "fuzzyness");

		return std::make_shared<Metal>(albedo, fuzzyness);
	}

	if (materialType == "Dielectric") {
		double refractiveIndex = get_variable_or_error<double>(table, "refractive_index");

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

	auto cameraTable = get_table_or_error(table, "camera");
	Camera camera = parse_camera_table(cameraTable, (double) width / height);

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

		scene.add(hittableObject);
	}


	std::cout << "[RayTracer] Rendering scene:\n";
	std::cout << "  Title: " << sceneTitle << "\n";
	std::cout << "  Width: " << width << "\n";
	std::cout << "  Height: " << height << "\n";
	std::cout << "  Samples per pixel: " << samples << "\n";
	std::cout << "  Camera position: " << camera.origin() << "\n";
	std::cout << "  " << scene.size() << " objects\n";

	std::shared_ptr<BVHNode> sceneBVH = std::make_shared<BVHNode>(scene);
	HittableList final_;
	final_.add(sceneBVH);

	Tracer t (width, height, samples, camera, final_);
	t.render();

	return 0;
}
