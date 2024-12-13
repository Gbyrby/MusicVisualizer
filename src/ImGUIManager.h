#pragma once
#include "App.h"


class ImGUIManager {
public:
    ImGUIManager();
    void CreateInfoTab(bool* p_open, const int refreshRate, const int display_w, const int display_h, const int Vsync, const float vTime);
	
    void CreateOtherTab(bool* p_open, bool* themeStyle);
	
    void CreateDisplayTab(bool* p_open, int* Vsync, float* Scale, bool* fullscreeen_mode);

    void CreateAudioTab(bool* p_open);
};