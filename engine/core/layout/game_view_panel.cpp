#include "game_view_panel.hpp"

using hid::GameViewPanel;

void GameViewPanel::contents()
{
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

    ImGui::Image((ImTextureID)textureId, renderImageSize, ImVec2(0, 1), ImVec2(1, 0));
    // ImGui::PopStyleVar();
}
