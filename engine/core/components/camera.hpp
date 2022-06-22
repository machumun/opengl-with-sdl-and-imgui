#pragma once

#include "../interfaces/interface_component.hpp"
#include "../material.hpp"

namespace hid
{
    struct Camera : public hid::IComponent
    {
        static const std::size_t Type;
        virtual bool IsClassType(const std::size_t classType) const override;

        Camera(const float &width, const float &height);

        void configure(const glm::vec3 &position, const glm::vec3 &direction);

        glm::mat4 getProjectionMatrix() const;

        glm::mat4 getViewMatrix() const;

        glm::mat4 getCameraMatrix() const;

    private:
        const glm::mat4 projectionMatrix;
        const glm::vec3 up;
        glm::vec3 position;
        glm::vec3 target;
    };

}
