#include "WavefrontOBJParser.hpp"

#include <fstream>
#include <sstream>

bool WavefrontOBJParser::starts_with(const std::string& line, const std::string_view& seq) const {
	if (line.size() < seq.size())
		return false;

	for (size_t i = 0; i < seq.size(); ++i) {
		if (line[i] != seq[i])
			return false;
	}

	return true;
}

std::shared_ptr<Mesh> WavefrontOBJParser::parse(const std::shared_ptr<Material>& meshMaterial) const {
	std::ifstream fileStream (m_fileName);

	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<std::shared_ptr<Triangle>> faces;

	std::string line;
	while (std::getline(fileStream, line)) {
		if (starts_with(line, "vn")) {
			std::istringstream vecStream (line.substr(2));
			double x, y, z;
			vecStream >> x >> y >> z;
			normals.emplace_back(x, y, z);
		} else if (starts_with(line, "v")) {
			std::istringstream vecStream (line.substr(1));
			double x, y, z;
			vecStream >> x >> y >> z;
			vertices.emplace_back(x, y, z);
		} else if (starts_with(line, "f")) {
			std::istringstream faceStream (line.substr(1));
			std::array<Vec3, 3> faceVertices;
			std::array<Vec3, 3> faceNormals;
			for (size_t i = 0; i < 3; ++i) {
				size_t vertexIndex, normalIndex;
				faceStream >> vertexIndex;
				assert(faceStream.peek() == '/');
				faceStream.get();
				if (faceStream.peek() != '/') {
					size_t textureIndex;
					faceStream >> textureIndex;
				}
				assert(faceStream.peek() == '/');
				faceStream.get();
				faceStream >> normalIndex;

				assert(vertexIndex >= 1 && vertexIndex <= vertices.size());
				assert(normalIndex >= 1 && normalIndex <= normals.size());
				faceVertices[i] = vertices[vertexIndex - 1];
				faceNormals[i] = normals[normalIndex - 1];
			}

			faces.push_back(std::make_shared<Triangle>(
				faceVertices[0], faceVertices[1], faceVertices[2],
				faceNormals[0], faceNormals[1], faceNormals[2],
				nullptr
			));
		} else if (starts_with(line, "o") || starts_with(line, "#")) {
			continue;
		} else {
			std::cerr << "ERROR: " << line << '\n';
			assert(false);
		}
	}

	return std::make_shared<Mesh>(faces, meshMaterial);
}
