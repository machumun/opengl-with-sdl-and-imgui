#include "camera.hpp"

using hid::Camera;

const std::size_t Camera::Type = std::hash<std::string>()("Camera");

void Camera::onAddComponent()
{
    transform = object->transform;
}