#include "transform.hpp"

using hid::IComponent;
using hid::Transform;

const std::size_t Transform::Type{std::hash<std::string>()("Transform")};

bool Transform::IsClassType(const std::size_t classType) const
{
    if (classType == Transform::Type)
    {
        return true;
    }
    else
    {
        return hid::IComponent::IsClassType(classType);
    }
}

void Transform::update()
{
    const static std::string logTag{"hid::Transform::update"};
    updateModelMatrix();
}

void Transform::updateModelMatrix()
{
    modelMatrix = glm::translate(identity, position) *
                  glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                  glm::scale(identity, scale);
}

void Transform::updateForward(const float &rotationDegrees)
{
}

void Transform::inspector()
{
    if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
    {
        ImGui::DragFloat3("Position", (float *)&position, 10.f, -10.f);
        ImGui::DragFloat3("Scale", (float *)&scale, 10.f, -10.f);
        ImGui::TreePop();
    }
}

void Transform::rotateBy(const float &degrees)
{
    rotationDegrees = degrees;

    if (rotationDegrees > 360.0f)
    {
        rotationDegrees -= 360.0f;
    }
    else if (rotationDegrees < -360.0f)
    {
        rotationDegrees += 360.0f;
    }

    orientation = ::computeOrientation(identity, rotationDegrees, up);
    forward = ::computeForward(orientation);
}

void Transform::setPosition(const glm::vec3 &position)
{
    this->position = position;
}

// void setProjectionMatrix(const ){}

glm::mat4 Transform::getTransformMatrix() const
{
    return transformMatrix;
}

glm::mat4 Transform::getModelMatrix() const
{
    return modelMatrix;
}