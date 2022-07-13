#include "camera.hpp"

using hid::Camera;
using hid::IComponent;

const std::size_t Camera::Type = std::hash<std::string>()("Camera");

Camera::Camera(const float &width, const float &height)
    : projectionMatrix{glm::mat4{1.f}},
      cameraSize{width, height},
      angleOfView{60.f},
      nearfar{.001f, 100.f},
      background{glm::vec3{
          .3f,
          .3f,
          .3f}}
{
}

void Camera::onAddComponent()
{
    transform = object->transform;
}