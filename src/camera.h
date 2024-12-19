#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:

    enum class Dir {
        FRONT,
        REAR,
        LEFT,
        RIGHT,

        UP,
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f),
           float startYaw = -90.0f,
           float startPitch = 0.0f,
           float startSpeed = 2.5f,
           float startSensitivity = 0.05f,
           float startZoom = 45.0f);

    glm::mat4 getViewMatrix() const;

    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void processKeyboard(Dir direction, float deltaTime);

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    void processMouseScroll(float yOffset);

private:
    void updateCameraVectors();
};
