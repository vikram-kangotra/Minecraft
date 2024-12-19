#include "camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw,
               float startPitch, float startSpeed, float startSensitivity,
               float startZoom)
    : position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch),
      movementSpeed(startSpeed), mouseSensitivity(startSensitivity), zoom(startZoom) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboard(Dir direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    switch (direction) {
        case Dir::FRONT: position += front * velocity; break; 
        case Dir::REAR: position -= front * velocity; break;
        case Dir::LEFT: position -= right * velocity; break;
        case Dir::RIGHT: position += right * velocity; break;
        case Dir::UP: position += up * velocity; break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
    zoom -= (float)yOffset;
    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 45.0f) zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
