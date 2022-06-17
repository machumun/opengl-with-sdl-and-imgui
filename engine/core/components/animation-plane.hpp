#pragma once

#include "../object.hpp"
#include "../material.hpp"

struct AnimationPlane : public hid::Object
{
    std::string mesh;
    uint32_t animationFrame;
    hid::Material material;

    AnimationPlane(
        const hid::Material &material,
        const uint32_t &animationFrame,
        const glm::vec3 &position = glm::vec3{0.0f, 0.0f, 0.0f},
        const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
        const glm::vec3 &rotationAxis = glm::vec3{0.0f, 1.0f, 0.0f},
        const float &rotationDegrees = 0.0f)
        : mesh{"plane"},
          animationFrame(animationFrame),
          material(material){};

    void setBaseColor(const glm::vec3 &color)
    {
        material.baseColor = color;
    };

    hid::Material getMaterial() const
    {
        return material;
    }
};