// #include "opengl-asset-manager.hpp"
// #include "../../core/assets.hpp"
// #include <unordered_map>

// using hid::OpenGLAssetManager;

// struct OpenGLAssetManager::Internal
// {

//     std::unordered_map<hid::assets::Pipeline, hid::OpenGLPipeline> pipelineCache;
//     std::unordered_map<hid::assets::StaticMesh, hid::OpenGLMesh> staticMeshCache;
//     std::unordered_map<hid::assets::Texture, hid::OpenGLTexture> textureCache;
//     std::unordered_map<hid::assets::GLTF, hid::OpenGLGLTF> gltfCache;

//     Internal() {}

//     void loadPipelines(const std::vector<hid::assets::Pipeline> &pipelines)
//     {
//         for (const auto &pipeline : pipelines)
//         {

//             if (pipelineCache.count(pipeline) == 0)
//             {
//                 std::pair<std::string, std::string> pass = hid::assets::resolvePipelinePath(pipeline);
//                 pipelineCache.insert(std::make_pair(
//                     pipeline,
//                     hid::OpenGLPipeline(pass.first, pass.second)));
//             }
//         }
//     }

//     void loadStaticMeshes(const std::vector<hid::assets::StaticMesh> &staticMeshes)
//     {
//         for (const auto &staticMesh : staticMeshes)
//         {
//             if (staticMeshCache.count(staticMesh) == 0)
//             {
//                 staticMeshCache.insert(std::make_pair(
//                     staticMesh,
//                     hid::OpenGLMesh(hid::assets::loadOBJFile(hid::assets::resolveStaticMeshPath(staticMesh)))));
//             }
//         }
//     }

//     void loadTextures(const std::vector<hid::assets::Texture> &textures)
//     {
//         for (const auto &texture : textures)
//         {
//             if (textureCache.count(texture) == 0)
//             {
//                 textureCache.insert(std::pair(
//                     texture,
//                     hid::OpenGLTexture(hid::assets::loadBitmap(hid::assets::resolveTexturePath(texture)))));
//             }
//         }
//     }

//     void loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs)
//     {
//         for (const auto &gltf : gltfs)
//         {
//             if (gltfCache.count(gltf) == 0)
//             {
//                 gltfCache.insert(std::pair(
//                     gltf,
//                     hid::OpenGLGLTF(hid::assets::loadGLTF(hid::assets::resolveGLTFModelPath(gltf)))));
//             }
//         }
//     }
// };

// OpenGLAssetManager::OpenGLAssetManager() : internal(hid::make_internal_ptr<Internal>()) {}

// void OpenGLAssetManager::loadPipelines(const std::vector<hid::assets::Pipeline> &pipelines)
// {
//     internal->loadPipelines(pipelines);
// }

// void OpenGLAssetManager::loadStaticMeshes(const std::vector<hid::assets::StaticMesh> &staticMeshes)
// {
//     internal->loadStaticMeshes(staticMeshes);
// }

// void OpenGLAssetManager::loadTextures(const std::vector<hid::assets::Texture> &textures)
// {
//     internal->loadTextures(textures);
// }

// void OpenGLAssetManager::loadGLTFModels(const std::vector<hid::assets::GLTF> &gltfs)
// {
//     internal->loadGLTFModels(gltfs);
// }

// hid::OpenGLPipeline &OpenGLAssetManager::getPipeline(const hid::assets::Pipeline &pipeline)
// {
//     return internal->pipelineCache.at(pipeline);
// }

// const hid::OpenGLMesh &OpenGLAssetManager::getStaticMesh(const hid::assets::StaticMesh &staticMesh) const
// {
//     return internal->staticMeshCache.at(staticMesh);
// }

// const hid::OpenGLTexture &OpenGLAssetManager::getTexture(const hid::assets::Texture &texture) const
// {
//     return internal->textureCache.at(texture);
// }

// const hid::OpenGLGLTF &OpenGLAssetManager::getGLTF(const hid::assets::GLTF &gltf) const
// {
//     return internal->gltfCache.at(gltf);
// };