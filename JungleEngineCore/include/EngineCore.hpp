//
// Created by artyr on 10.09.2023.
//

#ifndef JUNGLEENGINE_ENGINECORE_HPP
#define JUNGLEENGINE_ENGINECORE_HPP

#include "../../external/glad/include/glad/glad.h"
#include "../../external/glfw/include/GLFW/glfw3.h"
#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cstring>
#include "Shader.hpp"
#include "Camera.hpp"

namespace JEE {

    class EngineCore {
    private:

        const char *title;
        int windowWidth;
        int windowHeight;
        int returnCode;
        static bool resized;
        std::string textureDir = "../../JungleEngineCore/src/textures/";
        glm::vec4 bgColor = glm::vec4(0.5f, 0.5f, 0.9f, 1.0f);

        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;
        float lastX = 0.0f;
        float lastY = 0.0f;
        bool firstMouse = true;

        GLFWwindow *window;
        Shader shader = Shader(0);
        Camera camera;

    public:

        EngineCore(int width, int height, const char *_title);

        void Init();

        void PreRender();

        void AfterRender();

        bool Close();

        int getReturnCode() const;

        void Stop();

        void processInput();

        void renderCube(GLuint cubeVAO, GLuint cubeVBO, GLuint tex1 = 0, GLuint tex2 = 0, float x = 0.0f, float y = 0.0f, float z = 0.0f, char mode = 's');

        void renderPlane(GLuint planeVAO, GLuint planeVBO, GLuint tex1);

        GLuint generateTex(const char *texPath);

        static void resizeCallback(GLFWwindow *Window, int width, int height);

        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

        void checkResize();

        void setTexDir(std::string newDir);

        std::string concatenate(std::string str1, const std::string& str2);

        void setBGColor(float R, float G, float B, float A);

        void setShader(Shader newShader);
    };
}

#endif //JUNGLEENGINE_ENGINECORE_HPP