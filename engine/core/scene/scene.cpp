#include "scene.hpp"

using hid::Scene;

void Scene::instantiate(std::unique_ptr<hid::Object> &&object)
{
    object->scene = this;
    sceneData->objects.emplace_back(std::move(object));
}