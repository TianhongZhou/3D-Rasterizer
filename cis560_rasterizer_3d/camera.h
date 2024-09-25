#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

class Camera {
private:
    glm::vec4 forward;
    glm::vec4 right;
    glm::vec4 up;
    float fov;
    glm::vec4 pos;
    float near;
    float far;
    float aspect;

public:
    // Default constructor
    // Set member variables to default value
    Camera();
    ~Camera();

    // Return view matrix based on camera's local axes and position
    glm::mat4 viewMatrix() const;
    // Return perspective projection matrix based on clipping planes, aspect ratio and fov
    glm::mat4 projMatrix() const;
    // Translate the camera on forward direction
    void translateForward(float f);
    // Translate the camera on right direction
    void translateRight(float f);
    // Translate the camera on up direction
    void translateUp(float f);
    // Rotate the camera about right vector
    void rotateRight(float f);
    // Rotate the camera about up vector
    void rotateUp(float f);
    // Rotate the camera about forward vector
    void rotateForward(float f);
    // Getter
    glm::vec4 getPos() const;
};
