#pragma once

#include "wrapper/glm_wrapper.hpp"

namespace hid
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;

        bool operator==(const hid::Vertex &other) const;
    };
} // namespace

namespace std
{
    template <>
    struct hash<hid::Vertex>
    {
        size_t operator()(const hid::Vertex &vertex) const
        {
            return ((hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec2>()(vertex.texCoord) << 1)) >> 1);
        }
    };
} // namespace std