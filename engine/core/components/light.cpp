#include "light.hpp"

using hid::Light;

// CEREAL_REGISTER_TYPE(Light);
const std::size_t Light::Type = std::hash<std::string>()("Light");

Light::Light(
    const LightType &lightType,
    const glm::vec3 &color = glm::vec3{1.0f, 1.0f, 1.0f},
    const float &intensity = 1.0f)
    : lightType{lightType},
      color{color},
      intensity{intensity} {}