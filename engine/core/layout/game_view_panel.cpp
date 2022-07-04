#include "game_view_panel.hpp"
#include "../log.hpp"

using hid::GameViewPanel;

int GameViewPanel::textureId{1};
bool GameViewPanel::isWindowFocused{false};
bool GameViewPanel::isWindowHovered{false};
ImVec2 GameViewPanel::viewportBounds[2] = {{.0f, .0f}, {.0f, .0f}};

void GameViewPanel::contents()
{
    isWindowFocused = ImGui::IsWindowFocused();
    isWindowHovered = ImGui::IsWindowHovered();

    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    viewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
    viewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    // parent;
    if (layout == nullptr)
    {
        return;
    }
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::SliderInt("Texture ID", &textureId, 1, 10);
    static std::string logTag{"hid::GameView::contents"};
    ImVec2 wsize = ImGui::GetWindowSize();
    ImVec2 renderImageSize;
    // col or row ajustment

    if (wsize.x != 1280 && wsize.y != 800)
    {
        float aspectRatio = wsize.x / wsize.y;

        if (aspectRatio < 1.6f)
        {
            renderImageSize.x = wsize.x;
            renderImageSize.y = 800 * (wsize.x / 1280.f);
        }
        else
        {
            renderImageSize.x = 1280.f * (wsize.y / 800.f);
            renderImageSize.y = wsize.y;
        }
    }

    auto [mx, my] = ImGui::GetMousePos();
    uint32_t mouseX = mx - viewportBounds[0].x;
    uint32_t mouseY = my - viewportBounds[0].y;

    if (mouseX >= 0 && mouseY >= 0 && mouseX < wsize.x && mouseY < wsize.y)
    {
        // hid::log(logTag, std::to_string(mouseX));
    }

    ImGui::Image((ImTextureID)textureId, renderImageSize, ImVec2(0, 1), ImVec2(1, 0));
    // ImGui::PopStyleVar();
}
