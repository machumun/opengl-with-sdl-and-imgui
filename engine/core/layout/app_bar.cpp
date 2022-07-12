// #include "app_bar.hpp"
// #include "layout.hpp"

// #include <nfd.h>

// #include <iostream>

// using hid::AppBar;

// void AppBar::showAppBar(const bool &open)
// {
//     if (ImGui::BeginMenuBar())
//     {
//         fileMenu();
//         editMenu();
//         optionsMenu();
//         ImGui::EndMenuBar();
//     }
// }

// void AppBar::fileMenu()
// {
//     if (ImGui::BeginMenu("File"))
//     {
//         ImGui::MenuItem("(demo menu)", nullptr, false, false);
//         if (ImGui::MenuItem("New"))
//         {
//         }
//         if (ImGui::MenuItem("Open", "Ctrl+O"))
//         {
//         }
//         if (ImGui::BeginMenu("Open Recent"))
//         {
//             ImGui::MenuItem("fish_hat.c");
//             ImGui::MenuItem("fish_hat.inl");
//             ImGui::MenuItem("fish_hat.h");
//             if (ImGui::BeginMenu("More.."))
//             {
//                 ImGui::MenuItem("Hello");
//                 ImGui::MenuItem("Sailor");
//                 if (ImGui::BeginMenu("Recurse.."))
//                 {
//                     // ShowExampleMenuFile();
//                     ImGui::EndMenu();
//                 }
//                 ImGui::EndMenu();
//             }
//             ImGui::EndMenu();
//         }
//         if (ImGui::MenuItem("Save", "Ctrl+S"))
//         {

//             nfdchar_t *outPath = new nfdchar_t;
//             nfdresult_t result = NFD_OpenDialog("png,jpg;pdf", nullptr, &outPath);
//             if (result == NFD_OKAY)
//             {
//                 // hid::log(logTag, "NFD::Open" + outPath);
//                 std::cout << outPath << std::endl;
//                 delete outPath;
//             }
//             // do error handling

//             // if (ImGui::MenuItem("Save", "CTRL+S"))
//             // { /* do something */
//             // }

//             // ImGui::EndMenu();
//         }
//         if (ImGui::MenuItem("Save As.."))
//         {
//         }

//         ImGui::Separator();

//         if (ImGui::BeginMenu("Docking"))
//         {
//             static bool enabled = true;
//             ImGui::MenuItem("Enabled", "", &enabled);
//             ImGui::BeginChild("child", ImVec2(0, 60), true);
//             for (int i = 0; i < 10; i++)
//                 ImGui::Text("Scrolling Text %d", i);
//             ImGui::EndChild();
//             static float f = 0.5f;
//             static int n = 0;
//             ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
//             ImGui::InputFloat("Input", &f, 0.1f);
//             ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
//             ImGui::EndMenu();
//         }

//         if (ImGui::BeginMenu("Colors"))
//         {
//             float sz = ImGui::GetTextLineHeight();
//             for (int i = 0; i < ImGuiCol_COUNT; i++)
//             {
//                 const char *name = ImGui::GetStyleColorName((ImGuiCol)i);
//                 ImVec2 p = ImGui::GetCursorScreenPos();
//                 ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
//                 ImGui::Dummy(ImVec2(sz, sz));
//                 ImGui::SameLine();
//                 ImGui::MenuItem(name);
//             }
//             ImGui::EndMenu();
//         }

//         if (ImGui::BeginMenu("Options")) // <-- Append!
//         {
//             static bool b = true;
//             ImGui::Checkbox("SomeOption", &b);
//             ImGui::EndMenu();
//         }

//         if (ImGui::BeginMenu("Disabled", false)) // Disabled
//         {
//             IM_ASSERT(0);
//         }
//         if (ImGui::MenuItem("Checked", nullptr, true))
//         {
//         }
//         if (ImGui::MenuItem("Quit", "Alt+F4"))
//         {
//         }
//         ImGui::EndMenu();
//     }
// }

// void AppBar::editMenu()
// {
//     if (ImGui::BeginMenu("Edit"))
//     {
//         if (ImGui::MenuItem("Undo", "CTRL+Z"))
//         {
//         }
//         if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
//         {
//         } // Disabled item
//         ImGui::Separator();
//         if (ImGui::MenuItem("Cut", "CTRL+X"))
//         {
//         }
//         if (ImGui::MenuItem("Copy", "CTRL+C"))
//         {
//         }
//         if (ImGui::MenuItem("Paste", "CTRL+V"))
//         {
//         }
//         ImGui::EndMenu();
//     }
// }

// void AppBar::optionsMenu()
// {
//     if (ImGui::BeginMenu("Options"))
//     {
//         // Disabling fullscreen would allow the window to be moved to the front of other windows,
//         // which we can't undo at the moment without finer window depth/z control.
//         ImGui::MenuItem("Fullscreen", nullptr, &hid::Layout::opt_fullscreen);
//         ImGui::MenuItem("Padding", nullptr, &hid::Layout::opt_padding);
//         ImGui::Separator();

//         if (ImGui::MenuItem("Flag: NoSplit", "", (hid::Layout::dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))
//         {
//             hid::Layout::dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
//         }
//         if (ImGui::MenuItem("Flag: NoResize", "", (hid::Layout::dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))
//         {
//             hid::Layout::dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
//         }
//         if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (hid::Layout::dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
//         {
//             hid::Layout::dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
//         }
//         if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (hid::Layout::dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
//         {
//             hid::Layout::dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
//         }
//         if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (hid::Layout::dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, hid::Layout::opt_fullscreen))
//         {
//             hid::Layout::dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
//         }
//         ImGui::Separator();

//         if (ImGui::MenuItem("Close", nullptr, false))
//             hid::Layout::dockSpaceOpen = false;
//         ImGui::EndMenu();
//     }
// }