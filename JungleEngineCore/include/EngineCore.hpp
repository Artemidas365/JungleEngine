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

                float deltaTime = 0.0f;	// time between current frame and last frame
                float lastFrame = 0.0f;
                float lastX = 0.0f;
                float lastY = 0.0f;
                bool firstMouse = true;

                GLFWwindow *window;
                Shader ShaderProgram;
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

                void renderRect(GLuint tex1 = 0, GLuint tex2 = 0, float x = 0.0f, float y = 0.0f, float z = 0.0f);

                void drawRect();

                GLuint generateTex(const char *texPath);

                static void resizeCallback(GLFWwindow *Window, int width, int height);

                static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

                void checkResize();
            };
    }

#endif //JUNGLEENGINE_ENGINECORE_HPP