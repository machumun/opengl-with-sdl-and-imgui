#include "rect_transform.hpp"
#include "../wrapper/sdl_wrapper.hpp"

#include "../log.hpp"

using hid::RectTransform;
// CEREAL_REGISTER_TYPE(RectTransform);

const std::size_t RectTransform::Type = std::hash<std::string>()("RectTransform");

glm::vec2 RectTransform::unitPerDisplaySize = glm::vec2{2.f / hid::sdl::getDisplaySize().first, 2.f / hid::sdl::getDisplaySize().second};

void RectTransform::updateModelMatrix()
{
    modelMatrix = glm::translate(identity, glm::vec3{position, 0.f}) *
                  glm::rotate(identity, glm::radians(rotationDegrees), rotationAxis) *
                  glm::scale(identity, glm::vec3{scale * size * unitPerDisplaySize, 1.f});
}

void RectTransform::update()
{
    updateModelMatrix();
}

glm::mat4 RectTransform::getModelMatrix() const
{
    return modelMatrix;
}

void RectTransform::start()
{
    const static std::string logTag{"hid::RectTransform::start"};
    // hid::log(logTag, "Unit Per Display Size : " + std::to_string(unitPerDisplaySize.x));
}

void RectTransform::inspector()
{
    if (ImGui::TreeNodeEx((void *)Type,
                          ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                          "Rect Transform"))
    {
        ImGui::DragFloat2("Position", (float *)&position);
        ImGui::DragFloat2("Size", (float *)&size, .0f, 1000.f);
        ImGui::DragFloat2("Anchor", (float *)&anchor, 1.f, .0f);
        ImGui::DragFloat2("Scale", (float *)&scale, .0f, 10.0f);
        // ImGui::DragFloat2("unitPerDisplaySize", (float *)&unitPerDisplaySize);
        ImGui::TreePop();
    }
}
