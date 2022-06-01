#include "static-mesh-instance.hpp"

using hid::StaticMeshInstance;

struct StaticMeshInstance::Internal
{
    const hid::assets::StaticMesh mesh;
    hid::Material material;
    const glm::mat4 identity;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotationAxis;
    float rotationDegrees;
    glm::mat4 transformMatrix;
    glm::mat4 modelMatrix;

    Internal(const hid::assets::StaticMesh &mesh,
             const hid::Material &material,
             const glm::vec3 &position,
             const glm::vec3 &scale,
             const glm::vec3 &rotationAxis,
             const float &rotationDegrees)
        : mesh(mesh),
          material(material),
          identity(glm::mat4{1.0f}),
          position(position),
          scale(scale),
          rotationAxis(rotationAxis),
          rotationDegrees(rotationDegrees),
          transformMatrix(identity),
          modelMatrix(identity)
    {
    }

    void update(const glm::mat4 &projectionViewMatrix)
    {

        transformMatrix = projectionViewMatrix *
                          glm::translate(identity, position) *
                          glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                          glm::scale(identity, scale);
    }

    void updateModelMatrix()
    {
        modelMatrix = glm::translate(identity, position) *
                      glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                      glm::scale(identity, scale);
    }

    void rotateBy(const float &degrees)
    {
        rotationDegrees += degrees;

        if (rotationDegrees > 360.0f)
        {
            rotationDegrees -= 360.0f;
        }
        else if (rotationDegrees < -360.0f)
        {
            rotationDegrees += 360.0f;
        }
    }
};

StaticMeshInstance::StaticMeshInstance(
    const hid::assets::StaticMesh &staticMesh,
    const hid::Material &material,
    const glm::vec3 &position,
    const glm::vec3 &scale,
    const glm::vec3 &rotationAxis,
    const float &rotationDegrees)
    : internal(hid::make_internal_ptr<Internal>(
          staticMesh,
          material,
          position,
          scale,
          rotationAxis,
          rotationDegrees)) {}

void StaticMeshInstance::update(const glm::mat4 &projectionViewMatrix)
{
    internal->update(projectionViewMatrix);
}

void StaticMeshInstance::updateModelMatrix()
{
    internal->updateModelMatrix();
}

void StaticMeshInstance::rotateBy(const float &degrees)
{
    internal->rotateBy(degrees);
}

void StaticMeshInstance::setPosition(const glm::vec3 &position)
{
    internal->position = position;
}

void StaticMeshInstance::setBaseColor(const glm::vec3 &color)
{
    internal->material.baseColor = color;
};

hid::assets::StaticMesh StaticMeshInstance::getMesh() const
{
    return internal->mesh;
}

hid::Material StaticMeshInstance::getMaterial() const
{
    return internal->material;
}

glm::mat4 StaticMeshInstance::getTransformMatrix() const
{
    return internal->transformMatrix;
}

glm::mat4 StaticMeshInstance::getModelMatrix() const
{
    return internal->modelMatrix;
}
