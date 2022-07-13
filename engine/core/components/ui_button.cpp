#include "ui_button.hpp"
#include "../../application/application.hpp"

#include "../log.hpp"

#include "../scene/scene.hpp"

using hid::Application;
using hid::UIButton;

// CEREAL_REGISTER_TYPE(UIButton);

const std::size_t UIButton::Type = std::hash<std::string>()("UIButton");

UIButton::UIButton()
    : isSelected{false},
      texture{"empty"},
      staticMesh{Application::assetManager->getStaticMesh("ui_plane")},
      callback{nullptr},
      pressedColor{glm::vec3{
          1.f,
          1.f,
          1.f}},
      shaderReference{Application::assetManager->getShader("ui")}

{
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
    shaderReference->enableAlphaBlend();
    shaderReference->useProgram();
    shaderReference->setTexture(texture);
    shaderReference->setVec3("u_baseColor", &pressedColor[0]);
    shaderReference->setMat4("u_modelMatrix", &rectTransfrom->getModelMatrix()[0][0]);
    staticMesh->draw();
    shaderReference->disableAlphaBlend();
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
