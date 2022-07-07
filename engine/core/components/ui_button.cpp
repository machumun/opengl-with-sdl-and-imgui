#include "ui_button.hpp"
#include "../../application/application.hpp"

#include "../log.hpp"

#include "../scene/scene.hpp"

using hid::Application;
using hid::UIButton;

const std::size_t UIButton::Type = std::hash<std::string>()("UIButton");

UIButton::UIButton(const std::string &texture = "empty")
    : isSelected{false},
      texture{texture},
      staticMesh{Application::assetManager->getStaticMesh("ui_plane")},
      callback{nullptr},
      pressedColor{glm::vec3{
          1.f,
          1.f,
          1.f}},
      shaderReference{Application::assetManager->getShader("ui")}
{
    // rectTransfrom = &object->getComponent<hid::RectTransform>();
    // rectTransfrom->size = glm::vec2{width, height};
}

void UIButton::update()
{
}

void UIButton::start()
{
    camera = object->scene->mainCameraReference;
    canvas = &object->parent->getComponent<Canvas>();
}

void UIButton::draw()
{
    shaderReference->useProgram();

    shaderReference->setTexture(texture);
    shaderReference->setVec3("u_baseColor", &pressedColor[0]);
    shaderReference->setMat4("u_modelMatrix", &rectTransfrom->getModelMatrix()[0][0]);
    staticMesh->draw();
}

void UIButton::inspector()
{
    if (ImGui::TreeNodeEx((void *)Type,
                          ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen,
                          "Button"))
    {
        ImGui::ColorPicker3("Pressed Color", (float *)&pressedColor);
        ImGui::InputText("Texture", &texture);
        ImGui::TreePop();
    }
}


void UIButton::onAddComponent()
{
    rectTransfrom = &object->getComponent<hid::RectTransform>();
}
