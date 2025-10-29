#pragma once

/** STD */
#include <vector>

/** GLM */
#include <glm/vec3.hpp>

namespace stl {

class Mesh {
  private:
    const std::vector<glm::vec3> _vertices;
    const std::vector<glm::vec3> _normalVectors;

    const unsigned int _verticesCount;
    const unsigned int _pointCount;

  public:
    Mesh(const std::vector<glm::vec3> &vertices);
    Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normalVectors);
    ~Mesh();

    std::vector<glm::vec3> getVertices() const;
    std::vector<float> getPoints() const;

    /**
     * Return normal vectors of the mesh
     */
    std::vector<glm::vec3> getNormalVectors() const;

    unsigned int getVerticesCount() const;
    unsigned int getPointCount() const;
};

} // namespace stl