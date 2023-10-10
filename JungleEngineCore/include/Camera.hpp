//
// Created by artyr on 10.10.2023.
//

#ifndef JUNGLEENGINE_CAMERA_HPP
#define JUNGLEENGINE_CAMERA_HPP


#include "../../external/glad/include/glad/glad.h"
#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"
#include <iostream>

namespace JEE {

        enum Camera_Movement {
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT
            };

    // Default camera values
        const float YAW = -90.0f;
        const float PITCH = 0.0f;
        const float SPEED = 2.5f;
        const float SENSITIVITY = 0.1f;
        const float ZOOM = 45.0f;


        class Camera {
            private:


                glm::vec3 camPos;
                glm::vec3 camTarget;
                glm::vec3 camUp;
                glm::vec3 camRight;
                glm::vec3 camFront;
                glm::vec3 worldUp;

                float yaw;
                float pitch;

                float movementSpeed;
                float mouseSensitivity;

                void updateCameraVectors();

            public:
                static float zoom;

                Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                       float yaw = YAW, float pitch = PITCH);

                Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

                glm::mat4 GetViewMatrix();

                void ProcessKeyboard(Camera_Movement direction, float deltaTime);

                void ProcessMouseMovement(float Xoffset, float Yoffset, GLboolean constrainPitch = GL_TRUE);

                static void ProcessMouseScroll(float yoffset);
            };
    }

#endif //JUNGLEENGINE_CAMERA_HPP
