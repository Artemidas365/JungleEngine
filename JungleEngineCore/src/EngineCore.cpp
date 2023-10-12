//
// Created by artyr on 10.09.2023.
//

#include "EngineCore.hpp"

#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace JEE {

    bool EngineCore::resized = true;

    EngineCore::EngineCore(int width, int height, const char *_title) :
            windowWidth(width), windowHeight(height), title(_title) {
        returnCode = 0;
        glfwInit();
        window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
        camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    }

    void EngineCore::Init() {

        if (!glfwInit())
            returnCode = -1;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            returnCode = -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, resizeCallback);
        glfwSetScrollCallback(window, scroll_callback);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            returnCode = -1;
        }

        glViewport(0, 0, windowWidth, windowHeight);
        glEnable(GL_DEPTH_TEST);
        ShaderProgram.CreateShader("../../JungleEngineCore/src/shaders/VertexShader.vert",
                                   "../../JungleEngineCore/src/shaders/FragmentShader.frag");

    }

    void EngineCore::processInput() {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {

            if (glfwGetWindowMonitor(window) == NULL) {
                // fullscreen
                GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
                const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
                glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
                windowWidth = mode->width;
                windowHeight = mode->height;
            } else {
                // windowed
                windowWidth = 800;
                windowHeight = 600;
                glfwSetWindowMonitor(window, NULL, 100, 100, windowWidth, windowHeight, GLFW_DONT_CARE);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
            double xpos;
            double ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset);
        }
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstMouse = true;
        }
    }

    void EngineCore::PreRender() {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        processInput();
        checkResize();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShaderProgram.use();

        glm::mat4 view = camera.GetViewMatrix();
        ShaderProgram.setMat4("view", view);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(Camera::zoom), (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);
        ShaderProgram.setMat4("projection", projection);
    }

    void EngineCore::AfterRender() {
        glfwSwapBuffers(window);
        glUseProgram(0);
    }

    void EngineCore::drawRect() {
        float vertices[] = {
                // positions                        // texture coords
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top left
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
                1, 0, 3, // first triangle
                1, 2, 3,  // second triangle
                3, 2, 6,
                3, 7, 6,
                4, 5, 6,
                4, 7, 6,
                0, 1, 5,
                0, 4, 5,
                1, 5, 6,
                1, 2, 6,
                0, 4, 7,
                0, 3, 7
        };
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // bind Texture
        ShaderProgram.use();
        ShaderProgram.setInt("texture1", 0);
        ShaderProgram.setInt("texture2", 1);


    }

    void EngineCore::renderRect(GLuint tex1, GLuint tex2, float x, float y, float z) {

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, z)) *
                glm::rotate(model, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        ShaderProgram.setMat4("model", model);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2);

        // render container
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }

    GLuint EngineCore::generateTex(const char *fileName) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(concatenate(textureDir, fileName).c_str() , &width, &height, &nrChannels, 0);
        if (data) {
            if(nrChannels == 3){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else if(nrChannels == 4){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else {
                std::cout << "image has unknown format with " << nrChannels << " channels." << std::endl;
            }

        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        return texture;
    }

    bool EngineCore::Close() {
        return glfwWindowShouldClose(window);
    }

    void EngineCore::Stop() {
        glDeleteProgram(ShaderProgram.ID);

        glfwTerminate();
        returnCode = 0;
    }

    void EngineCore::resizeCallback(GLFWwindow *Window, int width, int height) {
        glViewport(0, 0, width, height);
        EngineCore::resized = true;
    }

    void EngineCore::checkResize(){
        if(EngineCore::resized){
            glfwGetWindowSize(window, &windowWidth, &windowHeight);
            EngineCore::resized = false;
        }
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    void EngineCore::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Camera::ProcessMouseScroll(static_cast<float>(yoffset));
    }

    std::string EngineCore::concatenate(std::string str1, const std::string& str2){
        str1.append(str2);

        return str1;
    }

    int EngineCore::getReturnCode() const {
        return returnCode;
    }

    void EngineCore::setTexDir(std::string newDir) {
        textureDir = std::move(newDir);
    }
}
