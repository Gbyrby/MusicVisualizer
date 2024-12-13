#pragma once
#include "Utils.h"

#define GLEW_STATIC
#include "GL/glew.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGUIManager.h"


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}



class APP {
public:
    GLFWwindow* window;
    int static display_w, display_h;
    static int Vsync;
    static bool show_demo_window;
    static bool show_another_window;

    int vScreenSizeLocation = 0;
    int vTimeLocation = 0;
    int vColorBackgroundLocation = 0;
    int vColorLocation = 0;
    int vRotationLocation = 0;
    int vAudioLocation = 0;
    int vReactLocation = 0;
    int vInteractionPointLocation = 0;
    int vInteractionLocation = 0;

    float color[18] = {
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };
    float Audio[3] = {
        1.0f, 1.0f, 1.0f,
    };
    float Rotation[9] = {
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
    };
    float React[3] = {
        1.0f, 1.0f, 1.0f,

    };
    float InteractionPoint[2] = {
        0.0f, 0.0f
    };
    float Interaction = 0.0f;

 
    



    APP(int ScrenWidth = 1280, int ScreenHeight = 720);

    void MainLoop();
    
    ~APP();

private:
    void UpdateShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
};