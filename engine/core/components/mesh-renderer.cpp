#include "mesh-renderer.hpp"

using hid::MeshRenderer;

const std::size_t MeshRenderer::Type = std::hash<std::string>()("MeshRenderer");
bool MeshRenderer::IsClassType(const std::size_t classType) const
{
    if (classType == MeshRenderer::Type)
    {
        return true;
    }
    else
    {
        return hid::IComponent::IsClassType(classType);
    }
}

MeshRenderer::MeshRenderer(const std::string &mesh,
                           const hid::Material &material)
    : mesh{mesh},
      material{material} {}

std::string MeshRenderer::getMesh() const
{
    return mesh;
}

void MeshRenderer::setMesh(const std::string &mesh)
{
    this->mesh = mesh;
}

void MeshRenderer::setBaseColor(const glm::vec3 &color)
{
    material.baseColor = color;
};

hid::Material MeshRenderer::getMaterial() const
{
    return material;
}

void MeshRenderer::setMaterial(const hid::Material &material)
{
    this->material = material;
}