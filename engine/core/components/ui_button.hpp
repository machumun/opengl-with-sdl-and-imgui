#pragma once

#include "interface_component.hpp"
#include "rect_transform.hpp"
#include "canvas.hpp"
#include "camera.hpp"

#include "../object.hpp"
#include "../shader.hpp"
#include "../static_mesh.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include <functional>

namespace hid
{
    struct UIButton : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == UIButton::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        UIButton(const std::string &texture);

        void draw() override;

        void drawEditor() override
        {
        }

        void update() override;

        void onAddComponent() override;

        void start() override;

        void inspector() override;

    private:
        const hid::StaticMesh *staticMesh;
        glm::vec2 size;
        const hid::Shader *shaderReference;
        // const hid::Material material;
        hid::RectTransform *rectTransfrom;
        hid::RectTransform *parentRectTransform;
        hid::Canvas *canvas;
        bool isSelected;
        std::string texture;
        std::function<void()> callback;
        glm::vec3 pressedColor;

        hid::Camera *camera;
    };
}