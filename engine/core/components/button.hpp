#pragma once

#include "interface_component.hpp"
#include "rect_transform.hpp"
#include "canvas.hpp"

#include "../object.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include <functional>

namespace hid
{
    struct Button : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override
        {
            if (classType == Button::Type)
            {
                return true;
            }
            else
            {
                return hid::IComponent::IsClassType(classType);
            }
        };

        bool isSelected;
        std::string texture;
        SDL_Rect srect, drect;

        // std::function<void()> viewport = [&]() -> void
        // { return layout->viewport(); };

        std::function<void()> callback;

        Button(const int &width = 160,
               const int &height = 30)
            : isSelected{false},
              texture{"empty"},
              mesh{"plane"},
              rectTransfrom{&object->getComponent<hid::RectTransform>()},
              callback{nullptr},
              srect{width, height}
        {
        }

        void drawRuntime() override
        {
        }

        void update() override
        {
            // if (SDL_HasIntersection)
            // {
            // }
        }

        void start()
        {
            // rectTransfrom = &object->getComponent<RectTransform>();
            canvas = &object->parent->getComponent<Canvas>();
        }

        void inspector() override
        {
        }

    private:
        const std::string mesh;
        hid::RectTransform *rectTransfrom;
        hid::Canvas *canvas;
    };
}