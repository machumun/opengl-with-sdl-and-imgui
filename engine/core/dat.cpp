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
        ImGui::Begin("SDL with OpenGL"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("THIS IS MY HAMSTER.");      // Display some text (you can use a format strings too)
        ImGui::Checkbox("Is Active", &isActive); // Edit bools storing our window open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("rotate speed", &rotateSpeed, 0.0f, 100.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        if (ImGui::TreeNode("point light"))
        {
            ImGui::SliderFloat("strength", &pointLightStrength, 0.0f, 3.0f);
            ImGui::SliderFloat3("position", (float *)&pointLightPosition, 0.0f, 1.0f);
            ImGui::ColorEdit4("color", (float *)&pointLightColor);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("ambient light"))
        {
            ImGui::SliderFloat("strength", &ambientLightStrength, 0.0f, 3.0f);
            ImGui::ColorEdit4("color", (float *)&ambientLightColor);
            ImGui::TreePop();
        }

        // ImGui::ColorEdit4("light color", (float *)&pointLightColor); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))
        {
            ::counter++;
        } // Buttons return true when clicked (most widgets return true when edited/activated)

        ImGui::SameLine();
        ImGui::Text("counter = %d", ::counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}