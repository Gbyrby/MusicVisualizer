//#define GLEW_STATIC
#include "GL/glew.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>


// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

#include <vector>

class Renderer {
public:
	Renderer();
	~Renderer();
	void UpdateShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
	bool WindowShouldClose = false;

	void Draw(std::vector<double>& FFTData);

	bool play = false;
	bool UseFFT = true;
	bool UseSmooth = true;
	bool ShowLines = true;
	int smoothStep = 10;
	int segmentLenght = 2048;
	float sensitivity = 1.f;
	
private:
	ImGuiIO* io;
	GLFWwindow* window;
	ImVec4 clear_color;

	bool show_demo_window;
	bool show_another_window;

	int vScreenSizeLocation = 0;
	int vTimeLocation = 0;
	int vColorBackgroundLocation = 0;
	int vColorLocation = 0;
	int vRotationLocation = 0;
	int vAudioLocation = 0;
	int vReactLocation = 0;
	int vInteractionPointLocation = 0;
	int vInteractionLocation = 0;
	unsigned int shaderProgram = 0;

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
		0.0f, 0.0f, 0.0f,

	};
	float InteractionPoint[2] = {
		0.0f, 0.0f
	};
	float Interaction = 0.0f;


};