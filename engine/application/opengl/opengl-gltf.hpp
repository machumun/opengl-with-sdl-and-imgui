#pragma once

#include <map>
#include "../../core/gltf.hpp"
#include "opengl-mesh.hpp"
#include "opengl-texture.hpp"

#include <string>

namespace hid
{

    struct OpenGLGLTF
    {
        hid::GLTF gltf;

        std::vector<hid::OpenGLMesh> meshes;
        std::vector<hid::OpenGLTexture> textures;
        std::vector<glm::vec4> matrices;

        OpenGLGLTF(const hid::GLTF &gltf) : gltf{hid::GLTF{gltf}}
        {
            for (const auto &mesh : gltf.meshes)
            {
                meshes.emplace_back(hid::OpenGLMesh{mesh});
            }

            for (const auto &tex : gltf.textures)
            {
                textures.emplace_back(hid::OpenGLTexture{tex});
            }
        }

        void draw(const hid::OpenGLShader &shader) const;
    };
}