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

    /**
     * Convert glm:vec3 vector to array of floats as required
     * by OpenGL. This function also extend the number of vectors
     * so that we can send normal vector per vertex. See the note.
     *
     * This function return number of normal vectors constituents three
     * times bigger then number of normal vectors. See the note below.
     *
     * NOTE: We can't pass normal vectors per face(in our case triangle),
     *       so this function is used to extend the number of normal vectors
     *       in the array, so that we can send normal vector per vertex.
     *
     * @return Array of floats filled with normal vectors
     */
    std::vector<float> getNormalVectorPoints() const;

    unsigned int getVerticesCount() const;
    unsigned int getPointCount() const;
};

} // namespace stl