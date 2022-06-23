#pragma once

#include "components/transform.hpp"
#include "interfaces/interface_component.hpp"

// #include "log.hpp"

namespace hid
{
    struct Object
    {
        std::string name;

        Object(const std::string &name)
            : name{name.c_str()},
              componentsIterator{components.begin()}
        {
            this->addComponent<hid::Transform>();
        }

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
            std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(params)...);
            component->parent = this;
            components.emplace_back(std::move(component));
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

            return *std::unique_ptr<T>(nullptr);
        }

        template <class T>
        bool hasComponent()
        {
            for (auto &&component : components)
            {
                if (component->IsClassType(T::Type))
                {
                    return true;
                }
            }

            return false;
        }

        void update()
        {
            // const static std::string logTag{"component update"};
            for (auto &&component : components)
            {
                component->update();
            }
        }

        void start()
        {
            for (auto &&component : components)
            {
                component->start();
            }
        }

        // private:
        std::vector<std::unique_ptr<hid::IComponent>> components;
        std::vector<std::unique_ptr<hid::IComponent>>::iterator componentsIterator;
    };
}
