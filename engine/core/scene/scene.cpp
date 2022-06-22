#include "scene.hpp"

using hid::Scene;

void Scene::instantiate(std::shared_ptr<hid::Object> object)
{
    sceneData->objects.emplace_back(object);
}