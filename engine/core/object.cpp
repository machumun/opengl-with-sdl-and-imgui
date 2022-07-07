#include "object.hpp"

// #include "scene/scene.hpp"

using hid::Object;

Object::Object(const std::string &name)
    : name{name.c_str()},
      componentsIterator{components.begin()},
      isActive{true},
      isStatic{false}
{
}

const void Object::draw() const
{
    if (isActive)
    {
        for (auto &&component : components)
        {
            component->draw();
        }

        for (auto &&child : children)
        {
            child->draw();
        }
    }
}

void Object::update()
{
    // const static std::string logTag{"component update"};
    for (auto &&component : components)
    {
        component->update();
    }
    for (auto &&child : children)
    {
        child->update();
    }
}

void Object::start()
{
    for (auto &&component : components)
    {
        component->start();
    }
    for (auto &&child : children)
    {
        child->start();
    }
}

void Object::addChild(std::unique_ptr<hid::Object> &&child)
{
    children.emplace_back(std::move(child));
}

void Object::setId(const uint32_t &hash)
{
    id = hash;
}

bool Object::operator==(const Object &obj)
{
    return id == obj.id;
}