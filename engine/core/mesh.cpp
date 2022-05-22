#include "mesh.hpp"

using hid::Mesh;

struct Mesh::Internal
{

    const std::vector<hid::Vertex> vertices;
    const std::vector<uint32_t> indices;

    Internal(const std::vector<hid::Vertex> &vertices, const std::vector<uint32_t> &indices)
        : vertices(vertices), indices(indices)
    {
    }
};


Mesh::Mesh(const std::vector<hid::Vertex> &vertices, const std::vector<uint32_t> &indices)
    : internal(hid::make_internal_ptr<Internal>(vertices, indices)) {}

const std::vector<hid::Vertex> &Mesh::getVertices() const
{
    return internal->vertices;
}

const std::vector<uint32_t> &Mesh::getIndices() const
{
    return internal->indices;
}