#pragma once

#include <map>
#include "../../core/gltf.hpp"
#include "opengl_mesh.hpp"
#include "opengl_texture.hpp"

#include <string>

namespace hid
{

    struct OpenGLGLTF
    {
        hid::GLTF gltf;

        std::vector<std::string> meshes;
        std::vector<std::string> textures;
        std::vector<glm::vec4> matrices;

        OpenGLGLTF(const hid::GLTF &gltf) : gltf{hid::GLTF{gltf}}
        {
            // for (const auto &mesh : gltf.meshes)
            // {
            //     meshes.emplace_back(hid::OpenGLMesh{mesh});
            // }

            // for (const auto &tex : gltf.textures)
            // {
            //     textures.emplace_back(hid::OpenGLTexture{tex});
            // }
        }

        void draw(const hid::OpenGLShader &shader) const;
    };
}