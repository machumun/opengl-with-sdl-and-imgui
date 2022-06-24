#pragma once

#include "interface_component.hpp"
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

        void inspector()
        {
            if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Mesh Renderer"))
            {
                ImGui::InputText("Mesh", &mesh);
                if (ImGui::TreeNodeEx((void *)(Type + 1), ImGuiTreeNodeFlags_DefaultOpen, "Material"))
                {
                    ImGui::InputText("Albedo", &material.albedo);
                    ImGui::ColorPicker3("BaseColor", (float *)&material.baseColor);
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }

    private:
        std::string mesh;
        hid::Material material;
    };

}
