#include "camera.h"

Camera::Camera()
    : forward(glm::vec4(0.f, 0.f, -1.f, 0.f)),
    right(glm::vec4(1.f, 0.f, 0.f, 0.f)),
    up(glm::vec4(0.f, 1.f, 0.f, 0.f)),
    fov(45.f),
    pos(glm::vec4(0.f, 0.f, 10.f, 1.f)),
    near(0.01f), far(100.f), aspect(1.f)
{}

Camera::~Camera() {}

glm::vec4 Camera::getPos() const {
    return this->pos;
}

// Translate the camera on forward direction
void Camera::translateForward(float f) {
    pos += f * forward;
}

// Translate the camera on right direction
void Camera::translateRight(float f) {
    pos += f * right;
}

// Translate the camera on up direction
void Camera::translateUp(float f) {
    pos += f * up;
}

// Rotate the camera about right vector
void Camera::rotateRight(float f) {
    // We need to negate the degree due to it's a left handed system
    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), -f, glm::vec3(right));

    up = glm::vec4(glm::vec3(rotation * up), 0.f);
    forward = glm::vec4(glm::vec3(rotation * forward), 0.f);

    up = glm::normalize(up);
    forward = glm::normalize(forward);
}

// Rotate the camera about up vector
void Camera::rotateUp(float f) {
    // We need to negate the degree due to it's a left handed system
    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), -f, glm::vec3(up));

    right = glm::vec4(glm::vec3(rotation * right), 0.f);
    forward = glm::vec4(glm::vec3(rotation * forward), 0.f);

    right = glm::normalize(right);
    forward = glm::normalize(forward);
}

// Rotate the camera about forward vector
void Camera::rotateForward(float f) {
    // We need to negate the degree due to it's a left handed system
    glm::mat4 rotation = glm::rotate(glm::mat4(1.f), -f, glm::vec3(forward));

    up = glm::vec4(glm::vec3(rotation * up), 0.f);
    right = glm::vec4(glm::vec3(rotation * right), 0.f);

    up = glm::normalize(up);
    right = glm::normalize(right);
}

// Return view matrix based on camera's local axes and position
glm::mat4 Camera::viewMatrix() const {
    glm::mat4 view_orient(1.f);

    view_orient[0] = right;
    view_orient[1] = up;
    view_orient[2] = forward;
    view_orient = glm::transpose(view_orient);

    glm::mat4 view_trans(1.f);
    view_trans[3] = -pos;
    view_trans[3][3] = 1.f;

    return view_orient * view_trans;
}

// Return perspective projection matrix based on clipping planes, aspect ratio and fov
glm::mat4 Camera::projMatrix() const {
    glm::mat4 result(0.f);
    float fov_part = 1.f / (tan(fov / 2.f));

    result[0][0] = fov_part / aspect;
    result[1][1] = fov_part;
    result[2][2] = far / (far - near);
    result[3][2] = -far * near / (far - near);
    result[2][3] = 1.f;

    return result;
}
