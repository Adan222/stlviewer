#include "BinaryReader.hpp"

/** STD */
#include <cstring>
#include <iostream>
#include <vector>

/** GLM */
#include <glm/vec3.hpp>

/** STL */
#include "stl/Mesh.hpp"
#include "stl/Reader.hpp"

/** Constructors */

stl::BinaryReader::BinaryReader(std::ifstream &&ifstream) : stl::Reader(std::move(ifstream)) {}

stl::BinaryReader::~BinaryReader() {}

/** Public methods */

stl::Mesh stl::BinaryReader::read() const {
    // Skip 80-byte header
    _fstream.seekg(80, std::ios::beg);

    uint32_t triangleCount = 0;
    _fstream.read(reinterpret_cast<char *>(&triangleCount), sizeof(uint32_t));

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normalVectors;

    for (uint32_t i = 0; i < triangleCount; ++i) {
        StlBinaryTriangle rawTriangle;
        _fstream.read(reinterpret_cast<char *>(&rawTriangle), sizeof(StlBinaryTriangle));

        // Normal vector
        glm::vec3 normalVector;
        normalVector.x = rawTriangle.normal.x;
        normalVector.y = rawTriangle.normal.y;
        normalVector.z = rawTriangle.normal.z;
        normalVectors.emplace_back(normalVector);

        // Vertices
        for (int v = 0; v < 3; ++v) {
            vertices.emplace_back(glm::vec3(rawTriangle.vertices[v].x,
                                            rawTriangle.vertices[v].y,
                                            rawTriangle.vertices[v].z));
        }
    }

    return Mesh(vertices, normalVectors);
}
