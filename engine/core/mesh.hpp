#pragma once

#include "internal-ptr.hpp"
#include "vertex.hpp"
#include <vector>

namespace hid
{
    struct Mesh
    {
        const std::vector<hid::Vertex> vertices;
        const std::vector<uint32_t> indices;

        Mesh(const std::vector<hid::Vertex> &vertices, const std::vector<uint32_t> &indices)
            : vertices(vertices), indices(indices) {}

        const std::vector<hid::Vertex> &Mesh::getVertices() const
        {
            return vertices;
        }

        const std::vector<uint32_t> &Mesh::getIndices() const
        {
            return indices;
        }
    };
}