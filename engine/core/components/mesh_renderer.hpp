#pragma once

#include "interface_component.hpp"

#include "camera.hpp"

#include "../../application/application.hpp"

#include "../material.hpp"
#include "../shader.hpp"
#include "../static_mesh.hpp"

#include "../scene/scene.hpp"

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
            shaderReference->useProgram();

            // glActiveTexture(GL_TEXTURE0);
            shaderReference->setMat4("u_projectionMatrix", &camera->getCameraMatrix()[0][0]);

            shaderReference->setTexture(material.albedo);
            shaderReference->setVec3("u_baseColor", &material.baseColor[0]);
            shaderReference->setMat4("u_modelMatrix", &transform->getModelMatrix()[0][0]);
            staticMesh->draw();
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
            camera = object->scene->mainCameraReference;
            transform = object->transform;
            shaderReference = Application::assetManager->getShader(material.shader);
            staticMesh = Application::assetManager->getStaticMesh(mesh);
        }

        void setStaticMesh(const std::string &newMesh)
        {
            mesh = newMesh;
            staticMesh = Application::assetManager->getStaticMesh(mesh);
        }

        // caches
    private:
        std::string mesh;
        hid::Material material;
        hid::Shader *shaderReference;
        hid::StaticMesh *staticMesh;
        hid::Camera *camera;
        hid::Transform *transform;
    };

}
