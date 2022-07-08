#include "game_view_panel.hpp"
#include "../log.hpp"
#include "../wrapper/sdl_wrapper.hpp"
#include "../wrapper/glm_wrapper.hpp"

#include "../../application/application.hpp"

using hid::GameViewPanel;

int GameViewPanel::textureId{1};
bool GameViewPanel::isWindowFocused{false};
bool GameViewPanel::isWindowHovered{false};
ImVec2 GameViewPanel::viewportBounds[2] = {{.0f, .0f}, {.0f, .0f}};

void GameViewPanel::contents()
{
    static const auto displaySize = hid::sdl::getDisplaySize();
    static const std::string logTag{"hid::GameViewPanel::contents"};

    isWindowFocused = ImGui::IsWindowFocused();
    isWindowHovered = ImGui::IsWindowHovered();

    ImGui::SliderInt("Texture ID", &textureId, 1, 10);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    // parent;
    if (layout == nullptr)
    {
        return;
    }
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImVec2 wsize = ImGui::GetWindowSize();
    ImVec2 renderImageSize;
    // col or row ajustment

    if (wsize.x != displaySize.first && wsize.y != displaySize.second)
    {
        float aspectRatio = wsize.x / wsize.y;

        if (aspectRatio < 1.6f)
        {
            renderImageSize.x = wsize.x;
            renderImageSize.y = displaySize.second * (wsize.x / displaySize.first);
        }
        else
        {
            renderImageSize.x = displaySize.first * (wsize.y / displaySize.second);
            renderImageSize.y = wsize.y;
        }
    }

    if (isWindowFocused)
    {
        if (Application::inputManager->mouseButtonPressed(MouseButtons::LEFT))
        {
            auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
            auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
            auto viewportOffset = ImGui::GetWindowPos();
            viewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
            viewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};
            auto mousePosition = Application::inputManager->getMousePos();

            auto [mx, my] = ImGui::GetMousePos();
            uint32_t mouseX = mx - viewportBounds[0].x;
            uint32_t mouseY = my - viewportBounds[0].y;

            if (mouseX >= 0 && mouseY >= 0 && mouseX < wsize.x && mouseY < wsize.y)
            {
                hid::log(logTag, "Plessed left mouse btn.X: " + std::to_string(mouseX));
                // hid::log(logTag, "mx : " + std::to_string(mx));
                // hid::log(logTag, "mousePosition.x : " + std::to_string(mousePosition.x));
            }
        }
        else if (Application::inputManager->mouseButtonReleased(MouseButtons::LEFT))
        {
            hid::log(logTag, "Up mouse btn.");
        }
    }

    ImGui::Image((ImTextureID)textureId, renderImageSize, ImVec2(0, 1), ImVec2(1, 0));
    // ImGui::PopStyleVar();
}
