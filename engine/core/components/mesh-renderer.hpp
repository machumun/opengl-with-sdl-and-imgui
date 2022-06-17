#pragma once

#include "../interfaces/IComponent.hpp"
#include "../material.hpp"

namespace hid
{
    struct MeshRenderer : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override;

        MeshRenderer() = default;
        MeshRenderer(
            const std::string &mesh,
            const hid::Material &material);

        std::string getMesh() const;

        void setMesh(const std::string &mesh);

        void setBaseColor(const glm::vec3 &color);

        hid::Material getMaterial() const;

        void setMaterial(const hid::Material &material);

        void update() override {}

    private:
        std::string mesh;
        hid::Material material;
    };

}
