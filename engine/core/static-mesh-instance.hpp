#pragma once

#include "asset-inventory.hpp"
#include "glm-wrapper.hpp"
#include "internal-ptr.hpp"
#include "material.hpp"

namespace hid
{
    struct StaticMeshInstance
    {
        StaticMeshInstance(
            const hid::assets::StaticMesh &staticMesh,
            const hid::Material &material,
            const glm::vec3 &position = glm::vec3{0.0f, 0.0f, 0.0f},
            const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec3 &rotationAxis = glm::vec3{0.0f, 1.0f, 0.0f},
            const float &rotationDegrees = 0.0f);

        void update(const glm::mat4 &projectionViewMatrix);
        void updateModelMatrix();

        void rotateBy(const float &degrees);
        void setPosition(const glm::vec3 &position);
        void setBaseColor(const glm::vec3 &color);

        hid::assets::StaticMesh getMesh() const;
        hid::Material getMaterial() const;
        glm::mat4 getTransformMatrix() const;
        glm::mat4 getModelMatrix() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}