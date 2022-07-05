#include "scene.hpp"

#include <ctime>
#include <cstdlib>

using hid::Scene;

// staticMeshCache.count(staticMesh.first) == 0

void Scene::instantiate(std::unique_ptr<hid::Object> &&object)
{
    object->scene = this;
    // object->setId(sceneData->objects.size() + 1);
    while (true)
    {
        std::srand(time(nullptr));
        uint32_t randomize = std::rand();

        // check
        for (auto &object : sceneData->objects)
        {
            if (randomize == object->id)
            {
                continue;
            }
        }

        object->setId(randomize);

        sceneData->objects.emplace_back(std::move(object));

        break;
    }
}

void Scene::instantiate(std::unique_ptr<hid::Object> &&object, const std::unique_ptr<hid::Object> &parent)
{
    object->scene = this;
    // object->setId(sceneData->objects.size() + 1);
    while (true)
    {
        std::srand(time(nullptr));
        uint32_t randomize = std::rand();

        // check
        for (auto &child : parent->children)
        {
            if (randomize == child->id)
            {
                continue;
            }
        }

        object->parent = parent.get();

        object->setId(randomize);
        parent->addChild(std::move(object));
        // parent->children.emplace_back(std::move(object));

        break;
    }
}

void updateEditor(const float &delta)
{
}