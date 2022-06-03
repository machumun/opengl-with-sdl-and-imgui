#include "dat.hpp"

#include <memory>
#include <string>

using hid::Dat;

namespace
{
    uint32_t counter = 0;
}

void Dat::init()
{
}

void Dat::userImGui()
{
    {
        ImGui::Begin("DEMO Window"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("My Hamsters");              // Display some text (you can use a format strings too)
        ImGui::Checkbox("Is Active", &isActive); // Edit bools storing our window open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("rotate speed", &rotateSpeed, 0.0f, 100.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        if (ImGui::TreeNode("point light"))
        {
            ImGui::SliderFloat("intensity", &lightSettings.pointLight.intensity, 0.0f, 10.0f);
            ImGui::SliderFloat3("position", (float *)&lightSettings.pointLight.position, -10.0f, 10.0f);
            ImGui::ColorEdit3("color", (float *)&lightSettings.pointLight.color);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("ambient light"))
        {
            ImGui::SliderFloat("intensity", &lightSettings.ambientLight.intensity, 0.0f, 10.0f);
            ImGui::ColorEdit3("color", (float *)&lightSettings.ambientLight.color);
            ImGui::TreePop();
        }
        ImGui::Checkbox("Bloom", &lightSettings.bloom);
        ImGui::SliderFloat("blur intensity", &lightSettings.bloomIntensity, 0.0f, 10.0f);

        if (ImGui::Button("Button"))
        {
            ::counter++;
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", ::counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}