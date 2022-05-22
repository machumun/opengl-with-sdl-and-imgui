#pragma once
#include "../../core/graphics-wrapper.hpp"
#include "../../core/mesh.hpp"

namespace hid
{

    struct OpenGLMesh
    {
        OpenGLMesh(const hid::Mesh &mesh);

        const GLuint &getVertexBufferId() const;

        const GLuint &getIndexBufferId() const;

        const uint32_t &getNumIndices() const;

        void draw() const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}