#include "Mesh.hpp"

/** Constructors */

stl::Mesh::Mesh(const std::vector<glm::vec3> &vertices)
    : _vertices(vertices), _verticesCount(vertices.size()), _pointCount(vertices.size() * 3) {}

stl::Mesh::~Mesh() {}

/** Public methods */

std::vector<glm::vec3> stl::Mesh::getVertices() const { return _vertices; }

std::vector<float> stl::Mesh::getPoints() const {
    const std::vector<glm::vec3> rawVertices = getVertices();

    std::vector<float> rawFloats;
    for (const glm::vec3 &v : rawVertices) {
        rawFloats.emplace_back(v.x);
        rawFloats.emplace_back(v.y);
        rawFloats.emplace_back(v.z);
    }

    return rawFloats;
}

unsigned int stl::Mesh::getVerticesCount() const { return _verticesCount; }

unsigned int stl::Mesh::getPointCount() const { return _pointCount; }
