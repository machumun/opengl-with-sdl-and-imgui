#include "animation_plane.hpp"

#include "../log.hpp"

using hid::AnimationPlane;
// using hid::IComponent;

// CEREAL_REGISTER_TYPE(AnimationPlane)
// CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponent, AnimationPlane)

const std::size_t AnimationPlane::Type = std::hash<std::string>()("AnimationPlane");

AnimationPlane::AnimationPlane(
    const hid::Material &material,
    const std::vector<uint32_t> animationFrame,
    const uint32_t &skipFrame,
    const uint32_t &spriteUnitsU,
    const uint32_t &spriteUnitsV)
    : mesh{"plane"},
      animationFrame{animationFrame},
      animationFrameSize{animationFrame.size()},
      skipFrame{skipFrame},
      spriteUnitsU{spriteUnitsU},
      spriteUnitsV{spriteUnitsV},
      material{material},
      frameCount{0},
      animationCount{0},
      spriteUnitsWidth{1 / (float)spriteUnitsU},
      spriteUnitsHeight{1 / (float)spriteUnitsV} {}

void AnimationPlane::update()
{
    static const std::string logTag{"hid::AnimationPlane::update"};

    if (frameCount < skipFrame)
    {
        ++frameCount;
    }
    else
    {
        frameCount = 0;
        ++animationCount;
        if (animationCount == animationFrameSize)
        {
            animationCount = 0;
        }
    }
}

void AnimationPlane::onAddComponent()
{

    transform = object->transform;
    shaderReference = Application::assetManager->getShader(material.shader);
    staticMesh = Application::assetManager->getStaticMesh(mesh);
}

hid::Material AnimationPlane::getMaterial() const
{
    return material;
}

const uint32_t AnimationPlane::getCurrentAnimationFrame() const
{
    static const std::string logTag{"hid::AnimationPlane::getCurrentAnimationFrame"};

    return animationFrame[animationCount];
}

const glm::vec2 AnimationPlane::getCurrentOffsetUV() const
{
    const uint32_t currentAnimationFrame = getCurrentAnimationFrame();
    float offsetUnitsU = (currentAnimationFrame % spriteUnitsU) * spriteUnitsWidth;
    float offsetUnitsV = (currentAnimationFrame / spriteUnitsV) * spriteUnitsHeight;

    return glm::vec2{offsetUnitsU, offsetUnitsV};
}

const glm::vec2 AnimationPlane::getSpriteUnits()
{
    return glm::vec2{spriteUnitsU, spriteUnitsV};
}

void AnimationPlane::draw()
{
    if (material.alphaBlend)
    {
        shaderReference->enableAlphaBlend();
    }

    shaderReference->useProgram();
    shaderReference->setMat4("u_projectionMatrix", &camera->getCameraMatrix()[0][0]);
    shaderReference->setTexture(material.albedo);
    shaderReference->setVec3("u_baseColor", &material.baseColor[0]);
    shaderReference->setMat4("u_modelMatrix", &transform->getModelMatrix()[0][0]);
    shaderReference->setVec2("u_currentOffsetUV", &getCurrentOffsetUV()[0]);
    shaderReference->setVec2("u_spliteNum", &getSpriteUnits()[0]);
    staticMesh->draw();

    if (material.alphaBlend)
    {
        shaderReference->disableAlphaBlend();
    }
}

void AnimationPlane::inspector()
{
    if (ImGui::TreeNodeEx((void *)Type, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen, "Animation Plane"))
    {
        ImGui::Text("Skip Frame %u", skipFrame);
        ImGui::Text("Frame Count %u", frameCount);
        ImGui::Text("Animation Count %u", animationCount);

        ImGui::TreePop();
    }
}

void AnimationPlane::start()
{
    camera = object->scene->mainCameraReference;
}