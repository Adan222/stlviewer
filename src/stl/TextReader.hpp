#pragma once

/** STD */
#include <vector>

/** GLM */
#include <glm/ext/vector_float3.hpp>

/** LIB STL */
#include "stl/Reader.hpp"

namespace stl {

class TextReader : public stl::Reader {
  private:
    /**
     * Clean line from white spaces
     */
    std::string cleanLine(const std::string &line) const;

    /**
     * Split line into array of strings
     */
    std::vector<std::string> split(const std::string &str, const std::string &delimeter) const;

    /**
     * Read line and get normal vector of the triangle
     *
     * @return Normal vector of the triangle
     */
    glm::vec3 readNormalVector(const std::vector<std::string> &line) const;

    /**
     * Read line and return vector for a vertex
     */
    glm::vec3 readVertex(const std::vector<std::string> &line) const;

  public:
    TextReader(std::ifstream &&ifstream);
    ~TextReader();

    stl::Mesh read() const override;
};

} // namespace stl