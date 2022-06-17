#pragma once

// #include "components/transform.hpp"
#include "interfaces/IComponent.hpp"

namespace hid
{
    struct Object
    {
        // components{std::make_shared<hid::Transform>()},
        Object()
            : componentsIterator{components.begin()} {}

        ~Object()
        {
            // for (auto component : components)
            // {
            //     delete component;
            // }
        }

        template <class T, typename... Args>
        void addComponent(Args &&...params)
        {
            components.emplace_back(std::make_shared<T>(std::forward<Args>(params)...));
        }

        template <class T>
        T &getComponent()
        {
            for (auto &&component : components)
            {
                if (component->IsClassType(T::Type))
                {
                    return *static_cast<T *>(component.get());
                }
            }

            return *std::shared_ptr<T>(nullptr);
        }

        void update()
        {
            for (auto &&component : components)
            {
                component->update();
            }
        }

        void draw()
        {
            for (auto &&component : components)
            {
                component->draw();
            }
        }

    private:
        std::vector<std::shared_ptr<hid::IComponent>> components;
        std::vector<std::shared_ptr<hid::IComponent>>::iterator componentsIterator;
    };
}
