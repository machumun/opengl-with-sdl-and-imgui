#pragma once

#include "transform.hpp"
#include "mesh.hpp"

namespace
{
    const glm::vec3 simplePlaneVerticePositions[4] = {
        {-1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
    };

    const glm::vec3 simplePlaneNormals[4] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    };

    const glm::vec2 simplePlaneUVs[4] = {
        {0.25f, 0.0f},
        {0.0f, 0.25f},
        {0.0f, 0.0f},
        {0.25f, 0.25f}};

    const std::vector<hid::Vertex> simplePlaneVertices{
        {simplePlaneVerticePositions[0], simplePlaneNormals[0], simplePlaneUVs[0]},
        {simplePlaneVerticePositions[1], simplePlaneNormals[1], simplePlaneUVs[1]},
        {simplePlaneVerticePositions[2], simplePlaneNormals[2], simplePlaneUVs[2]},
        {simplePlaneVerticePositions[3], simplePlaneNormals[3], simplePlaneUVs[3]},
    };

    const std::vector<uint32_t> simplePlaneIndices = {
        0, 1, 2, 3};

    const hid::Mesh simplePlaneMesh{simplePlaneVertices, simplePlaneIndices};
}

namespace hid
{
    struct AnimationPlane : public Transform
    {

        hid::assets::StaticMesh mesh;
        uint32_t animationFrame;
        hid::Material material;

        AnimationPlane(
            const hid::Material &material,
            const float &animationFrame,
            const glm::vec3 &position = glm::vec3{0.0f, 0.0f, 0.0f},
            const glm::vec3 &scale = glm::vec3{1.0f, 1.0f, 1.0f},
            const glm::vec3 &rotationAxis = glm::vec3{0.0f, 1.0f, 0.0f},
            const float &rotationDegrees = 0.0f)
            : mesh(hid::assets::StaticMesh::Plane),
              animationFrame(animationFrame),
              material(material),
              Transform(position, scale, rotationAxis, rotationDegrees){};

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