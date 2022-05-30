#pragma once

#include "../../core/asset-manager.hpp"
#include "../../core/internal-ptr.hpp"
#include "opengl-mesh.hpp"
#include "opengl-pipeline.hpp"
#include "opengl-texture.hpp"

namespace hid
{
    struct OpenGLAssetManager : public hid::AssetManager
    {
        OpenGLAssetManager();
        void loadPipelines(const std::vector<hid::assets::Pipeline> &pipelines) override;

        void loadStaticMeshes(const std::vector<hid::assets::StaticMesh> &staticMeshes) override;

        void loadTextures(const std::vector<hid::assets::Texture> &textures) override;

        hid::OpenGLPipeline &getPipeline(const hid::assets::Pipeline &pipeline);

        const hid::OpenGLMesh &getStaticMesh(const hid::assets::StaticMesh &staticMesh) const;

        const hid::OpenGLTexture &getTexture(const hid::assets::Texture &texture) const;

    private:
        struct Internal;
        hid::internal_ptr<Internal> internal;
    };
}