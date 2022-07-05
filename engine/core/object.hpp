#pragma once

#include "components/transform.hpp"
#include "components/rect_transform.hpp"

#include "components/interface_component.hpp"

// #include "log.hpp"

namespace hid
{
    struct Scene;

    struct Object
    {
        std::string name;
        hid::Transform *transform;

        uint32_t id;

        std::vector<std::unique_ptr<hid::IComponent>> components;
        std::vector<std::unique_ptr<hid::Object>> children;

        // paretnt : some children = 1 : n
        hid::Object *parent;

        hid::Scene *scene;
        std::vector<std::unique_ptr<hid::IComponent>>::iterator componentsIterator;

        Object(const std::string &name)
            : name{name.c_str()},
              componentsIterator{components.begin()}
        {
            this->addComponent<hid::Transform>();
            transform = &getComponent<Transform>();
        }

        Object(const std::string &name, const bool &isCanvasSpace)
            : name{name.c_str()},
              componentsIterator{components.begin()}
        {
            if (isCanvasSpace)
            {
                this->addComponent<hid::RectTransform>();
                // transform = &getComponent<RectTransform>();
            }
            else
            {
                this->addComponent<hid::Transform>();
                transform = &getComponent<Transform>();
            }
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
            component->object = this;
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

        const void drawRuntime() const
        {
            for (auto &&component : components)
            {
                component->drawRuntime();
            }

            for (auto &&child : children)
            {
                child->drawRuntime();
            }
        }

        void update()
        {
            // const static std::string logTag{"component update"};
            for (auto &&component : components)
            {
                component->update();
            }
            for (auto &&child : children)
            {
                child->update();
            }
        }

        void start()
        {
            for (auto &&component : components)
            {
                component->start();
            }
            for (auto &&child : children)
            {
                child->start();
            }
        }

        void addChild(std::unique_ptr<hid::Object> &&child)
        {
            children.emplace_back(std::move(child));
        }

        void setId(const uint32_t &hash)
        {
            id = hash;
        }

        bool operator==(const Object &obj)
        {
            return id == obj.id;
        }
    };
}
