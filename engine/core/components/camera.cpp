#include "camera.hpp"

using hid::Camera;

const std::size_t Camera::Type = std::hash<std::string>()("Camera");
bool Camera::IsClassType(const std::size_t classType) const
{
    if (classType == Camera::Type)
    {
        return true;
    }
    else
    {
        return hid::IComponent::IsClassType(classType);
    }
}

Camera::Camera(const float &width, const float &height)
    : projectionMatrix(glm::perspective(glm::radians(60.0f), width / height, 0.01f, 100.0f)),
      up(glm::vec3{0.0f, 1.0f, 0.0f}) {}

void Camera::configure(const glm::vec3 &position, const glm::vec3 &direction)
{
    this->position = position;
    this->target = position - direction;
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getCameraMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
};