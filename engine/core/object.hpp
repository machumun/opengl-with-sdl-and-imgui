#pragma once

#include "components/transform.hpp"
#include "components/rect_transform.hpp"

#include "components/interface_component.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

namespace hid
{
    struct Scene;

    enum class ObjectType
    {
        GAME_OBJECT,
        UI
    };

    struct Object
    {
        std::string name;
        hid::Transform *transform;
        hid::RectTransform *rectTransform;

        uint32_t id;

        std::vector<std::unique_ptr<hid::IComponent>> components;
        std::vector<std::unique_ptr<hid::Object>> children;

        // paretnt : some children = 1 : n
        hid::Object *parent;

        hid::Scene *scene;
        std::vector<std::unique_ptr<hid::IComponent>>::iterator componentsIterator;

        bool isActive;
        bool isStatic;

        Object(const std::string &name);

        ~Object() = default;

        template <class T, typename... Args>
        void addComponent(Args &&...params)
        {
            std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(params)...);
            component->object = this;
            component->onAddComponent();
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

        const void draw() const;

        void update();
        void start();

        void addChild(std::unique_ptr<hid::Object> &&child);

        void setId(const uint32_t &hash);
        bool operator==(const Object &obj);

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(cereal::make_nvp("name", name));
        }
    };
}
