#include "perspective-camera.hpp"

using hid::PerspectiveCamera;

PerspectiveCamera::PerspectiveCamera(const float &width, const float &height)
    : projectionMatrix(glm::perspective(glm::radians(60.0f), width / height, 0.01f, 100.0f)),
      up(glm::vec3{0.0f, 1.0f, 0.0f}) {}

void PerspectiveCamera::configure(const glm::vec3 &position, const glm::vec3 &direction)
{
    this->position = position;
    this->target = position - direction;
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::mat4 PerspectiveCamera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

glm::mat4 PerspectiveCamera::getCameraMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
};