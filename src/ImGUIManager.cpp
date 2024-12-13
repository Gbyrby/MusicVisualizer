#pragma once
#include "ImGUIManager.h"



ImGUIManager::ImGUIManager()
{
}

void ImGUIManager::CreateInfoTab(bool* p_open, const int refreshRate, const int display_w, const int display_h, const int Vsync, const float vTime) {
        if (*p_open) {
            ImGuiIO& io = ImGui::GetIO();


            ImGui::Begin("Info", p_open);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            if (Vsync) {
                ImGui::Text("FPS_CAP (MaxMonitorRefrashRate/vSync):%d (%d/%d) ", refreshRate / Vsync, refreshRate, Vsync);
            }
            else {
                ImGui::Text("FPS_CAP (MaxMonitorRefrashRate/vSync):UNLIMITED (%d/%d) ", refreshRate, Vsync);
            }
            ImGui::Text("Time %.3f", vTime);

#ifdef TIMEOUT
            ImGui::Text("Timeout time:%f", TIMEOUT_TIME - vTime);
#endif // TIMEOUT

            ImGui::Text("Screen Size %ix%i", display_w, display_h);

            ImGui::End();
        }
    }

void ImGUIManager::CreateOtherTab(bool* p_open, bool* themeStyle) {
        if (*p_open) {
            ImGui::Begin("Other", p_open);
            ImGui::Text("Light|Dark Theme");

            if (ImGui::Checkbox("Dark mode", themeStyle)) {
                if (*themeStyle) {
                    ImGui::StyleColorsDark();
                }
                else {
                    ImGui::StyleColorsLight();
                }
            }
            ImGui::End();
        }
    }

void ImGUIManager::CreateDisplayTab(bool* p_open, int* Vsync, float* Scale, bool* fullscreeen_mode) {
        if (*p_open) {
            ImGui::Begin("Display settings", p_open);
            ImGui::Text("Vsync");
            ImGui::SliderInt("##Vsync", Vsync, 0, 6);
            ImGui::Text("Resolution scale");
            ImGui::SliderFloat("##Scale", Scale, 1.f, 100.f, "%.2f%%");
            if (ImGui::Checkbox("Fullscreen mode", fullscreeen_mode)) {
                //if (!fullscreeen_mode) {
                //    // Switch to windowed mode

                //    glfwSetWindowMonitor(window, nullptr, 0, 0, display_w, display_h, 0);
                //    glfwMakeContextCurrent(window);
                //}
                //else {
                //    // Switch to fullscreen mode
                //    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
                //}
            }
            ImGui::End();
        }
    }

void ImGUIManager::CreateAudioTab(bool* p_open) {
        if (*p_open) {
            ImGui::Begin("Audio settings", p_open);
            if (ImGui::CollapsingHeader("Audio input")) {
                if (ImGui::TreeNode("Input file")) {
                    if (ImGui::Button("Select file")) {
                        ImGui::Text("Comming soon....");
                    }
                    ImGui::TreePop();
                }
            }

            if (ImGui::CollapsingHeader("Audio Output")) {
                if (ImGui::TreeNode("Select audio device")) {
                    if (ImGui::Button("Select audio device")) {
                        ImGui::Text("Comming soon....");
                    }
                    if (ImGui::Button("Analyze")) {
                        ImGui::Text("Comming soon....");
                    }
                    ImGui::TreePop();
                }
            }

            if (ImGui::CollapsingHeader("Audio analyzer algoritm")) {
                if (ImGui::TreeNode("Select audio analyzer algoritm")) {
                    const char* items[] = { "FFT", "MAX_VOLUME" };
                    static int item_current = 0;


                    ImGui::Combo("Select", &item_current, items, IM_ARRAYSIZE(items));
                    switch (item_current)
                    {
                    case 0:
                        ImGui::Text("FFT");
                        break;
                    default:
                        ImGui::Text("MAX_VOLUME");
                        break;
                    }
                    ImGui::TreePop();
                }


            }
            ImGui::End();
        }

    }
