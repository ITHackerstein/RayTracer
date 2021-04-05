#pragma once

#define TOML_EXCEPTIONS 0
#include <fstream>
#include <stdlib.h>
#include <toml++/toml.h>

#include "Materials/LambertianDiffuse.hpp"
#include "Materials/Metal.hpp"
#include "Materials/Dielectric.hpp"
#include "Materials/DiffuseLight.hpp"
#include "Textures/ImageTexture.hpp"
#include "Textures/WoodTexture.hpp"
#include "Textures/MarbleTexture.hpp"
#include "Textures/CheckerTexture.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/BVH.hpp"
#include "Tracer.hpp"
#include "Camera.hpp"

class SceneParser {
	public:
		SceneParser(char* fileName);

		Tracer::OutputImageOptions parse_output_image_options() const;
		Camera parse_camera() const;
		HittableList parse_objects() const;

		std::string_view scene_title() const { return m_sceneTitle; }

	private:
		template<typename T>
		static T get_key_or_error(const toml::table&, const char* key);

		template<typename T>
		static T get_key_or(const toml::table&, const char* key, T lastResort);

		static const toml::table& get_table_or_error(const toml::table&, const char* tableName);
		static const toml::array& get_array_or_error(const toml::table&, const char* arrayName);

		static Vec3 parse_vec3(const toml::array& vectorArray);
		static std::shared_ptr<Hittable> parse_hittable_object(const toml::table& hittableObject);
		static std::shared_ptr<Material> parse_material(const toml::table& materialObject);
		static std::shared_ptr<Texture> parse_texture(const toml::table& textureObject);

		toml::table m_sceneObject;
		std::string_view m_sceneTitle;
};
