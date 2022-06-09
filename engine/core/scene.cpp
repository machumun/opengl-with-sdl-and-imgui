#include "scene.hpp"

using hid::Scene;

void Scene::instantiate(hid::StaticMeshInstance &staticMeshInstance)
{
    sceneData->staticMeshInstances.emplace_back(
        std::make_shared<hid::StaticMeshInstance>(staticMeshInstance));
}

void Scene::instantiate(hid::AnimationPlane &animationPlane)
{
    sceneData->animationPlanes.emplace_back(
        std::make_shared<hid::AnimationPlane>(animationPlane));
}
