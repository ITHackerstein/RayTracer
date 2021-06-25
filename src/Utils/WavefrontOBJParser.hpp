#pragma once

#include <string_view>
#include "../Primitives/Mesh.hpp"

class WavefrontOBJParser {
	public:
		WavefrontOBJParser(const std::string& fileName):
			m_fileName(fileName) {}

		std::shared_ptr<Mesh> parse(const std::shared_ptr<Material>& meshMaterial) const;
	private:
		bool starts_with(const std::string& line, const std::string_view&) const;

		std::string m_fileName;
};
