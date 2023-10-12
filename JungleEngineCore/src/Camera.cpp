//
// Created by artyr on 10.10.2023.
//

#include "Camera.hpp"
namespace JEE {

    float Camera::zoom = ZOOM;

    void Camera::updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camFront = glm::normalize(front);
        // also re-calculate the Right and Up vector
        camRight = glm::normalize(glm::cross(camFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        camUp = glm::normalize(glm::cross(camRight, camFront));
    }

    Camera::Camera(glm::vec3 position, glm::vec3 up, float Yaw, float Pitch) :
            camFront(glm::vec3(0.0f, 0.0f, -1.0f)),
            movementSpeed(SPEED),
            mouseSensitivity(SENSITIVITY) {

        camPos = position;
        worldUp = up;
        yaw = Yaw;
        pitch = Pitch;
        updateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float Yaw, float Pitch) :
            camFront(glm::vec3(0.0f, 0.0f, -1.0f)),
            movementSpeed(SPEED),
            mouseSensitivity(SENSITIVITY) {

        camPos = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = Yaw;
        pitch = Pitch;
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(camPos, camPos + camFront, camUp);
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            camPos += camFront * velocity;
        if (direction == BACKWARD)
            camPos -= camFront * velocity;
        if (direction == LEFT)
            camPos -= camRight * velocity;
        if (direction == RIGHT)
            camPos += camRight * velocity;
    }

    void Camera::ProcessMouseMovement(float Xoffset, float Yoffset, GLboolean constrainPitch)
    {
        Xoffset *= mouseSensitivity;
        Yoffset *= mouseSensitivity;

        yaw   = glm::mod( yaw + Xoffset, 360.0f );
        pitch += Yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 80.0f)
            zoom = 80.0f;
    }
}
