#include "SceneParser.hpp"

SceneParser::SceneParser(char* fileName) {
	auto res = toml::parse_file(fileName);
	assert(res.succeeded() && "Error while trying to parse scene file!");

	m_sceneObject = res.table();
	m_sceneTitle = get_key_or_error<std::string_view>(m_sceneObject, "scene_title");
}

Tracer::OutputImageOptions SceneParser::parse_output_image_options() const {
	Tracer::OutputImageOptions res;
	res.imageWidth = get_key_or_error<size_t>(m_sceneObject, "width");
	res.imageHeight = get_key_or_error<size_t>(m_sceneObject, "height");
	res.samplesPerPixel = get_key_or_error<size_t>(m_sceneObject, "samples");
	res.outputFileName = get_key_or<const char*>(m_sceneObject, "save_to", "render.ppm");

	return res;
}

Camera SceneParser::parse_camera() const {
	auto cameraObject = get_table_or_error(m_sceneObject, "camera");

	auto cameraPositionArray = get_array_or_error(cameraObject, "position");
	auto cameraPosition = parse_vec3(cameraPositionArray);

	auto lookAtArray = get_array_or_error(cameraObject, "look_at");
	auto lookAt = parse_vec3(lookAtArray);

	auto fov = degrees_to_radians(get_key_or_error<double>(cameraObject, "fov"));
	auto lensAperture = get_key_or_error<double>(cameraObject, "lens_aperture");
	auto focusDistance = get_key_or_error<double>(cameraObject, "focus_distance");

	if (focusDistance < 0)
		focusDistance = (lookAt - cameraPosition).mag();

	auto width = get_key_or_error<size_t>(m_sceneObject, "width");
	auto height = get_key_or_error<size_t>(m_sceneObject, "height");
	double aspectRatio = (double) width / height;

	return Camera(cameraPosition, lookAt, fov, aspectRatio, lensAperture, focusDistance);
}

HittableList SceneParser::parse_objects() const {
	auto objectsArray = get_array_or_error(m_sceneObject, "objects");

	HittableList objectsList;

	for (auto& objectNode: objectsArray) {
		if (!objectNode.is_table()) {
			fprintf(stderr, "[TOML] Invalid object in 'objects' array!\n");
			exit(1);
		}

		auto object = parse_hittable_object(*(objectNode.as_table()));
		if (!object) {
			fprintf(stderr, "[TOML] Invalid object in 'objects' array!\n");
			exit(1);
		}

		objectsList.add(object);
	}

	auto bvhTree = std::make_shared<BVHNode>(objectsList);
	HittableList bvhList;
	bvhList.add(bvhTree);

	return bvhList;
}

template<typename T>
T SceneParser::get_key_or_error(const toml::table& table, const char* key) {
	auto v = table[key].value<T>();
	if (v.has_value())
		return *v;

	fprintf(stderr, "[TOML] Key '%s' not found or of invalid type!\n", key);
	exit(1);
}

template<typename T>
T SceneParser::get_key_or(const toml::table& table, const char* key, T lastResort) {
	auto v = table[key].value<T>();
	if (v.has_value())
		return *v;

	return lastResort;
}

const toml::table& SceneParser::get_table_or_error(const toml::table& table, const char* tableName) {
	auto node = table.get(tableName);
	if (!node) {
		fprintf(stderr, "[TOML] Table '%s' not found!\n", tableName);
		exit(1);
	}

	if (!node->is_table()) {
		fprintf(stderr, "[TOML] '%s' is not a table!\n", tableName);
		exit(1);
	}

	return *(node->as_table());
}

const toml::array& SceneParser::get_array_or_error(const toml::table& table, const char* arrayName) {
	auto node = table.get(arrayName);
	if (!node) {
		fprintf(stderr, "[TOML] Array '%s' not found!\n", arrayName);
		exit(1);
	}

	if (!node->is_array()) {
		fprintf(stderr, "[TOML] '%s' is not an array!\n", arrayName);
		exit(1);
	}

	return *(node->as_array());
}

Vec3 SceneParser::parse_vec3(const toml::array& vectorArray) {
	Vec3 v;

	if (vectorArray.size() != 3) {
		fprintf(stderr, "[TOML] Vector array has invalid length!\n");
		exit(1);
	}

	for (size_t axis = 0; axis < 3; ++axis) {
		auto axisValue = vectorArray.get(axis)->value<double>();
		if (!axisValue) {
			fprintf(stderr, "[TOML] Axis '%zu' of vector is not a number!\n", axis);
			exit(1);
		}

		v.e[axis] = *axisValue;
	}

	return v;
}

std::shared_ptr<Hittable> SceneParser::parse_hittable_object(const toml::table& hittableObject) {
	auto objectType = get_key_or_error<std::string_view>(hittableObject, "type");
	if (objectType == "Sphere") {
		auto centerArray = get_array_or_error(hittableObject, "center");
		auto center = parse_vec3(centerArray);

		auto radius = get_key_or_error<double>(hittableObject, "radius");

		auto materialObject = get_table_or_error(hittableObject, "material");
		auto material = parse_material(materialObject);
		if (!material) {
			fprintf(stderr, "[TOML] Invalid material!\n");
			exit(1);
		}

		return std::make_shared<Sphere>(center, radius, material);
	}

	return nullptr;
}

std::shared_ptr<Material> SceneParser::parse_material(const toml::table& materialObject) {
	auto materialType = get_key_or_error<std::string_view>(materialObject, "type");
	if (materialType == "LambertianDiffuse") {
		auto textureObject = get_table_or_error(materialObject, "albedo");
		auto texture = parse_texture(textureObject);
		if (!texture) {
			fprintf(stderr, "[TOML] Invalid texture!\n");
			exit(1);
		}

		return std::make_shared<LambertianDiffuse>(texture);
	}

	if (materialType == "Metal") {
		auto albedoVectorArray = get_array_or_error(materialObject, "albedo");
		auto albedo = parse_vec3(albedoVectorArray);

		auto fuzzyness = get_key_or_error<double>(materialObject, "fuzzyness");

		return std::make_shared<Metal>(albedo, fuzzyness);
	}

	if  (materialType == "Dielectric") {
		auto refractiveIndex = get_key_or_error<double>(materialObject, "refractive_index");

		return std::make_shared<Dielectric>(refractiveIndex);
	}

	return nullptr;
}

std::shared_ptr<Texture> SceneParser::parse_texture(const toml::table& textureObject) {
	auto textureType = get_key_or_error<std::string_view>(textureObject, "type");
	if (textureType == "SolidColor") {
		auto colorVectorArray = get_array_or_error(textureObject, "color");
		auto color = parse_vec3(colorVectorArray);

		return std::make_shared<SolidColor>(color);
	}

	if (textureType == "CheckerTexture") {
		auto oddTextureObject = get_table_or_error(textureObject, "odd");
		auto odd = parse_texture(oddTextureObject);

		auto evenTextureObject = get_table_or_error(textureObject, "even");
		auto even = parse_texture(evenTextureObject);

		return std::make_shared<CheckerTexture>(odd, even);
	}

	if (textureType == "MarbleTexture") {
		auto scale = get_key_or<double>(textureObject, "scale", 1.0);

		return std::make_shared<MarbleTexture>(scale);
	}

	if (textureType == "WoodTexture") {
		auto scale = get_key_or<double>(textureObject, "scale", 1.0);

		return std::make_shared<WoodTexture>(scale);
	}

	return nullptr;
}
