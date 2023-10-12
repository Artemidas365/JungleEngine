//
// Created by artyr on 24.09.2023.
//

#include "Shader.hpp"

namespace JEE {
    Shader::Shader(unsigned int id){
        ID = id;
    }

    Shader::Shader(const char *vertexPath, const char *fragmentPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        if (!vShaderFile.is_open()) {
            printf("\nFailed to open vertex file\n");
        }
        if (!fShaderFile.is_open()) {
            printf("\nFailed to open fragment file\n");
        } else {
            std::cout << "Files are open\n";

            char ch;
            while (vShaderFile.get(ch))
                vertexCode += ch;

            while (fShaderFile.get(ch))
                fragmentCode += ch;

            vShaderFile.close();
            fShaderFile.close();

            // 2. compile shaders
            // vertex shader
            unsigned int vertex;
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, reinterpret_cast<const GLchar *const *>(&vertexCode), NULL);
            glCompileShader(vertex);
            CheckCompilation(vertex);
            // fragment Shader
            unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, reinterpret_cast<const GLchar *const *>(&fragmentCode), NULL);
            glCompileShader(fragment);
            CheckCompilation(fragment);
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
    }

    // activate the shader
    void Shader::use() const {
        glUseProgram(ID);
    }


    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::CheckCompilation(GLuint shader) {

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            std::cerr << "Failed to compile shader:\n" << infoLog << std::endl;
            glDeleteShader(shader);
        } else {
            std::cout << "compiled shader\n" << std::endl;
        }
    }
}
