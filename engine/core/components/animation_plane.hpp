#pragma once

#include "camera.hpp"
#include "../shader.hpp"
#include "../static_mesh.hpp"
#include "../../application/application.hpp"

#include "interface_component.hpp"
#include "../material.hpp"

#include "../object.hpp"

#include "../scene/scene.hpp"

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

        // for draw cache pointer
        hid::Shader *shaderReference;
        hid::StaticMesh *staticMesh;
        hid::Camera *camera;
        hid::Transform *transform;

        AnimationPlane(
            const hid::Material &material,
            const std::vector<uint32_t> animationFrame,
            const uint32_t &skipFrame,
            const uint32_t &spriteUnitsU,
            const uint32_t &spriteUnitsV);

        hid::Material getMaterial() const;
        const uint32_t getCurrentAnimationFrame() const;
        const glm::vec2 getCurrentOffsetUV() const;
        const glm::vec2 getSpriteUnits();

        void update() override;
        void draw() override;
        void inspector() override;
        void onAddComponent() override;
        void start() override;
    };
}