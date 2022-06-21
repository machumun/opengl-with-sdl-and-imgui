#pragma once

#include "../core/wrapper/glm_wrapper.hpp"
#include "../core/internal-ptr.hpp"

namespace hid
{
    struct PerspectiveCamera
    {
        PerspectiveCamera(const float &width, const float &height);

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