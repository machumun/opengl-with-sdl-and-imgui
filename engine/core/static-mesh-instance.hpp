#pragma once

#include "transform.hpp"

namespace hid
{
    struct StaticMeshInstance : public Transform
    {
        hid::assets::StaticMesh mesh;
        hid::Material material;
        StaticMeshInstance(
            const hid::assets::StaticMesh &staticMesh,
            const hid::Material &material,
            const glm::vec3 &position = glm::vec3{0.0f, 0.0f, 0.0f},
            const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec3 &rotationAxis = glm::vec3{0.0f, 1.0f, 0.0f},
            const float &rotationDegrees = 0.0f)
            : mesh(staticMesh),
              material(material),
              Transform(position, scale, rotationAxis, rotationDegrees){};

        hid::assets::StaticMesh getMesh() const
        {
            return mesh;
        }

        void setBaseColor(const glm::vec3 &color)
        {
            material.baseColor = color;
        };

        hid::Material getMaterial() const
        {
            return material;
        }
    };
}