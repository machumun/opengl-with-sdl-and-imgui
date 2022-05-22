#pragma once

#include "internal-ptr.hpp"
#include "vertex.hpp"
#include <vector>

namespace hid
{

    struct Mesh
    {
        Mesh(const std::vector<hid::Vertex> &vertices, const std::vector<uint32_t> &indices);

        // const &A constはポインタの中身変更不可、アドレスの変更不可
        const std::vector<hid::Vertex> &getVertices() const;
        const std::vector<uint32_t> &getIndices() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}