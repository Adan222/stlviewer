#include "TextReader.hpp"

/** STD */
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/** GLM */
#include <glm/ext/vector_float3.hpp>

/** LIB STL */
#include "stl/Mesh.hpp"
#include "stl/Reader.hpp"

/** Private methods */

std::string stl::TextReader::cleanLine(const std::string &line) const {
    std::string s = line;

    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);

    return s;
}

std::vector<std::string> stl::TextReader::split(const std::string &str, const std::string &) const {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

glm::vec3 stl::TextReader::readNormalVector(const std::vector<std::string> &line) const {
    if (line[1] != "normal")
        throw std::runtime_error("Unknown keyword: " + line[1]);

    float x = std::stof(line[2]);
    float y = std::stof(line[3]);
    float z = std::stof(line[4]);

    return glm::vec3(x, y, z);
}

glm::vec3 stl::TextReader::readVertex(const std::vector<std::string> &line) const {
    try {
        float x = std::stof(line[1]);
        float y = std::stof(line[2]);
        float z = std::stof(line[3]);
        return glm::vec3(x, y, z);
    } catch (const std::exception &e) {
        std::cerr << "Failed to parse vertex: ";
        for (const auto &part : line)
            std::cerr << "[" << part << "] ";
        std::cerr << "\nError: " << e.what() << std::endl;
        throw;
    }
}
/** Constructors */

stl::TextReader::TextReader(std::ifstream &&ifstream) : stl::Reader(std::move(ifstream)) {}

stl::TextReader::~TextReader() {}

/** Public methods */

stl::Mesh stl::TextReader::read() const {
    unsigned int vertexIndex = 0;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normalVectors;

    std::string rawLine;
    for (std::string line; std::getline(_fstream, rawLine);) {
        if (rawLine.empty())
            continue;

        // Process and split line
        const std::string processedLine = cleanLine(rawLine);
        std::vector<std::string> lineList = split(processedLine, " ");

        // Check if line is empty
        if (lineList.empty())
            continue;

        const std::string &cmd = lineList[0];

        // TODO: What we should do with this?
        if (cmd == "solid") {
        }

        else if (cmd == "facet") {
            glm::vec3 normalVector = readNormalVector(lineList);
            normalVectors.emplace_back(normalVector);
        }

        else if (cmd == "outer" && lineList.size() > 1 && lineList[1] == "loop") {
            vertexIndex = 0;
        }

        else if (cmd == "vertex") {
            if (vertexIndex >= 3)
                throw std::runtime_error("Too many vertices in facet.");

            glm::vec3 v = readVertex(lineList);
            vertices.emplace_back(v);
            vertexIndex++;

        }

        else if (cmd == "endloop") {
        }

        else if (cmd == "endfacet") {
            if (vertexIndex != 3) {
                throw std::runtime_error("Incomplete triangle: vertex count = " +
                                         std::to_string(vertexIndex));
            }
        }

        else if (cmd == "endsolid")
            return stl::Mesh(vertices, normalVectors);

        else
            throw std::runtime_error("Unknown keyword: " + cmd);
    }

    throw std::runtime_error("Missing endsolid statement in STL file.");
}
