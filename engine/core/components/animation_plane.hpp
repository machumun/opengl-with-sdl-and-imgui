#pragma once

#include "camera.hpp"
#include "../shader.hpp"
#include "../static_mesh.hpp"
#include "../../application/application.hpp"

#include "interface_component.hpp"
#include "../material.hpp"

#include "../object.hpp"

#include "../scene/scene.hpp"

#include <utility>

namespace hid
{
    struct AnimationPlane : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == AnimationPlane::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        std::string mesh;
        const std::vector<uint32_t> animationFrame; // frame array for animation
        const size_t animationFrameSize;            // animation frame size
        const uint32_t skipFrame;                   // skipframe between animation frame
        const uint32_t spriteUnitsU;                // width, height per sprite unit
        const uint32_t spriteUnitsV;                // width, height per sprite unit
        const float spriteUnitsWidth;
        const float spriteUnitsHeight;
        hid::Material material; // for animation texture

        uint32_t frameCount;     // for frame
        uint32_t animationCount; // for animation

        hid::Shader *shaderReference;
        hid::StaticMesh *staticMesh;
        hid::Camera *camera;
        hid::Transform *transform;

        AnimationPlane(
            const hid::Material &material,
            const std::vector<uint32_t> animationFrame,
            const uint32_t &skipFrame,
            const uint32_t &spriteUnitsU,
            const uint32_t &spriteUnitsV)
            : mesh{"plane"},
              animationFrame{animationFrame},
              animationFrameSize{animationFrame.size()},
              skipFrame{skipFrame},
              spriteUnitsU{spriteUnitsU},
              spriteUnitsV{spriteUnitsV},
              material{material},
              frameCount{0},
              animationCount{0},
              spriteUnitsWidth{1 / (float)spriteUnitsU},
              spriteUnitsHeight{1 / (float)spriteUnitsV} {};

        hid::Material getMaterial() const
        {
            return material;
        }

        const uint32_t getCurrentAnimationFrame() const
        {
            static const std::string logTag{"hid::AnimationPlane::getCurrentAnimationFrame"};

            return animationFrame[animationCount];
        }

        const glm::vec2 getCurrentOffsetUV() const
        {
            const uint32_t currentAnimationFrame = getCurrentAnimationFrame();
            float offsetUnitsU = (currentAnimationFrame % spriteUnitsU) * spriteUnitsWidth;
            float offsetUnitsV = (currentAnimationFrame / spriteUnitsV) * spriteUnitsHeight;

            return glm::vec2{offsetUnitsU, offsetUnitsV};
        }

        const glm::vec2 getSpriteUnits()
        {
            return glm::vec2{spriteUnitsU, spriteUnitsV};
        }

        void update() override;

        void drawRuntime() override
        {
            shaderReference->useProgram();
            shaderReference->setMat4("u_projectionMatrix", &camera->getCameraMatrix()[0][0]);
            shaderReference->setTexture(material.albedo);
            shaderReference->setVec3("u_baseColor", &material.baseColor[0]);
            shaderReference->setMat4("u_modelMatrix", &transform->getModelMatrix()[0][0]);
            shaderReference->setVec2("u_currentOffsetUV", &getCurrentOffsetUV()[0]);
            shaderReference->setVec2("u_spliteNum", &getSpriteUnits()[0]);

            staticMesh->draw();
        }

        void inspector() override
        {
            if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Animation Plane"))
            {
                ImGui::Text("Skip Frame %u", skipFrame);
                ImGui::Text("Frame Count %u", frameCount);
                ImGui::Text("Animation Count %u", animationCount);

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
    };
}