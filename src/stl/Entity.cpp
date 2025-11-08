#include "Entity.hpp"

/** STD */
#include <iostream>
#include <vector>

/** GLM */
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

/** Lib OpenGL */
#include "opengl/VertexBufferObject.hpp"

/** Lib STL */
#include "stl/Mesh.hpp"

namespace stl {

Entity::Entity(const Mesh &mesh) : mesh(mesh), _vao(), _shaderProgram() {}

Entity::~Entity() {}

void Entity::setup() {
    // Create shaders
    Shader fragmentShader(Shader::Type::Fragment, "fragment.frag");
    fragmentShader.checkError();
    Shader vertexShader(Shader::Type::Vertex, "vertex.vert");
    vertexShader.checkError();

    // Programs
    _shaderProgram.attacheShader(vertexShader);
    _shaderProgram.attacheShader(fragmentShader);
    _shaderProgram.linkShaders();

    // VAO
    _vao.bind();

    /**
     * Configure attributes
     *
     * NOTE: that we have to set stride and startPointer to zero for each of attributes.
     * This is because we uses two separate VBOs for each attribute.
     */

    // Vertex position
    VertexBufferObject positionVbo;

    const int positionArraySize = mesh.getPoints().size();
    positionVbo.setData(mesh.getPoints().data(), sizeof(float) * positionArraySize);

    AttributeConfiguration vertexConfig = { .index = 0,
                                            .size = 3,
                                            .dataType = AttributeConfiguration::Type::FLOAT,
                                            .normalize = false,
                                            .stride = 0,
                                            .startPointer = 0 };
    _vao.configureAttribute(vertexConfig);

    // Normal vector position
    VertexBufferObject normalVbo;

    const int normalArraySize = mesh.getNormalVectorPoints().size();
    normalVbo.setData(mesh.getNormalVectorPoints().data(), sizeof(float) * normalArraySize);

    AttributeConfiguration normalConfig = { .index = 1,
                                            .size = 3,
                                            .dataType = AttributeConfiguration::Type::FLOAT,
                                            .normalize = false,
                                            .stride = 0,
                                            .startPointer = 0 };
    _vao.configureAttribute(normalConfig);
}

void Entity::setModelMatrix(const glm::mat4 &matrix) const {
    _shaderProgram.useProgram();
    _shaderProgram.setUniformMatrix4f("model", glm::value_ptr(matrix));
}

void Entity::setViewMatrix(const glm::mat4 &matrix) const {
    _shaderProgram.useProgram();
    _shaderProgram.setUniformMatrix4f("view", glm::value_ptr(matrix));
}

void Entity::setProjectionMatrix(const glm::mat4 &matrix) const {
    _shaderProgram.useProgram();
    _shaderProgram.setUniformMatrix4f("projection", glm::value_ptr(matrix));
}

void Entity::draw() const {
    _shaderProgram.useProgram();
    _vao.bind();

    glDrawArrays(GL_TRIANGLES, 0, mesh.getPointCount());
}

} // namespace stl