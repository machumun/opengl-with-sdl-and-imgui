#pragma once

#include "interface_component.hpp"
#include "../material.hpp"
#include "../scene/scene_data.hpp"

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

        hid::Material getMaterial() const;

        void setMaterial(const hid::Material &material);

        void update() override
        {
        }

        // for application update
        void draw() override
        {
            // scene->sceneData->assetManager;
            // //
            // shader.use();
            // glActiveTexture(GL_TEXTURE0);
            // shader.setMat4("u_projectionMatrix", &scene->getCameraMatrix()[0][0]);

            // const auto &modelMatrix = meshRenderer->parent->transform->getModelMatrix();
            // const auto &material = meshRenderer->getMaterial();

            // sceneData->assetManager->getTexture(material.albedo).bind();
            // shader.setVec3("u_baseColor", &material.baseColor[0]);
            // shader.setMat4("u_modelMatrix", &modelMatrix[0][0]);
            // sceneData->assetManager->getStaticMesh(meshRenderer->getMesh()).draw();
        }

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

        void start() override
        {
            scene = object->scene;
        }

    private:
        std::string mesh;
        hid::Material material;
        // hid::Shader *shader;
        hid::AssetManager *assetManager;
        hid::Scene *scene;
    };

}
