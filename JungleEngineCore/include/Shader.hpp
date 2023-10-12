//
// Created by artyr on 24.09.2023.
//

#ifndef JUNGLEENGINE_SHADER_HPP
#define JUNGLEENGINE_SHADER_HPP

#include "../../external/glad/include/glad/glad.h"
#include "../../external/glm/glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
namespace JEE {

    class Shader {
    public:
        Shader(unsigned int id);

        unsigned int ID;

        Shader(const char *vertexPath, const char *fragmentPath);

        void use() const;

        void setMat4(const std::string &name, const glm::mat4 &mat) const;

        void setMat3(const std::string &name, const glm::mat3 &mat) const;

        void setMat2(const std::string &name, const glm::mat2 &mat) const;

        void setVec4(const std::string &name, float x, float y, float z, float w) const;

        void setVec4(const std::string &name, const glm::vec4 &value) const;

        void setVec3(const std::string &name, float x, float y, float z) const;

        void setVec3(const std::string &name, const glm::vec3 &value) const;

        void setVec2(const std::string &name, float x, float y) const;

        void setVec2(const std::string &name, const glm::vec2 &value) const;

        void setFloat(const std::string &name, float value) const;

        void setInt(const std::string &name, int value) const;

        void setBool(const std::string &name, bool value) const;

        static void CheckCompilation(GLuint shader);

    };
}

#endif //JUNGLEENGINE_SHADER_HPP
