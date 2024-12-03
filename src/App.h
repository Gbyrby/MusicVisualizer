#include "Utils.h"
#include "Shader.h"
#include "GUI.h"



class APP {
    GLFWwindow* window;

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
            0.0f, 0.0f, 1.0f,
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



public:
    APP(int ScrenWidth = 800, int ScreenHeight = 800) {


        glfwSetErrorCallback(glfw_error_callback);
        glfwInit();


        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
        window = glfwCreateWindow(ScrenWidth, ScreenHeight, "Music Visualizer", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        glewInit();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);

        // Our state

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // build and compile our shader program
      // ------------------------------------
      // vertex shader
        
       

    };

    void MainLoop() {
        
        ImGuiIO& io = ImGui::GetIO();
        bool show_demo_window = false;
        bool show_another_window = false;
        static int Vsync = 1;
        while (!glfwWindowShouldClose(window)) {
            glfwSwapInterval(Vsync);

            float vTime = glfwGetTime() / 2;
            
            #ifdef TIMEOUT
            if (vTime > TIMEOUT_TIME) {
                std::cout << "QUIT BY TIMEOUT" << std::endl;
                break;}
            #endif // DEBUG
            int display_w, display_h;
            glfwGetFramebufferSize(this->window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            glfwPollEvents();
            if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
            {
                ImGui_ImplGlfw_Sleep(10);
                continue;
            }

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                (ImGui::ShowDemoWindow(&show_demo_window));

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            ImGui::Begin("Shader settings");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::Text("Time %.3f", vTime);
            ImGui::Text("Screen Size %ix%i", display_w, display_h);
            if (ImGui::Button("Button1")) {
                std::string vertexShaderString = FileSystem::ReadFile("ShaderCode/VertexShaders/VertexShader.txt");
                std::string fragmentShaderString = FileSystem::ReadFile("ShaderCode/FragmentShaders/Gradients.txt");
                const char* vertexShaderText = vertexShaderString.c_str();
                const char* fragmentShaderText = fragmentShaderString.c_str();
                UpdateShaders(vertexShaderText, fragmentShaderText);
               
            }

            if (ImGui::Button("Button2")) {
                std::string vertexShaderString = FileSystem::ReadFile("ShaderCode/VertexShaders/VertexShader.txt");
                std::string fragmentShaderString = FileSystem::ReadFile("ShaderCode/FragmentShaders/YandexBlob.txt");
                const char* vertexShaderText = vertexShaderString.c_str();
                const char* fragmentShaderText = fragmentShaderString.c_str();
                UpdateShaders(vertexShaderText, fragmentShaderText);
            }

            if (ImGui::Button("Button3")) {
                std::string vertexShaderString = FileSystem::ReadFile("ShaderCode/VertexShaders/VertexShader.txt");
                std::string fragmentShaderString = FileSystem::ReadFile("ShaderCode/FragmentShaders/PurpleYellowWaves.txt");
                const char* vertexShaderText = vertexShaderString.c_str();
                const char* fragmentShaderText = fragmentShaderString.c_str();
                UpdateShaders(vertexShaderText, fragmentShaderText);
            }


            ImGui::SliderInt("slider int", &Vsync, 0, 6);
            if (ImGui::CollapsingHeader("Color")) {
                float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.40f;
                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##1", (float*)&color[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##2", (float*)&color[3], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##3", (float*)&color[6], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##4", (float*)&color[9], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##5", (float*)&color[12], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

                ImGui::SetNextItemWidth(w);
                ImGui::ColorPicker3("##MyColor##6", (float*)&color[15], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
            };
            if (ImGui::CollapsingHeader("Rotation")) {
                ImGui::SliderFloat3("Rotation1", Rotation, 0, 1);
                ImGui::SliderFloat3("Rotation2", &Rotation[3], 0, 1);
                ImGui::SliderFloat3("Rotation3", &Rotation[6], 0, 1);
            }
            if (ImGui::CollapsingHeader("Audio")) {
                ImGui::SliderFloat3("Audio", Audio, 0, 3);
            }
            if (ImGui::CollapsingHeader("React")) {
                ImGui::SliderFloat3("React", React, 0, 1);
            }
            /* if (ImGui::CollapsingHeader("InteractionPoint (don`t work)")) {
                 ImGui::SliderFloat2("InteractionPoint", InteractionPoint, -1, 1);
             }
             if (ImGui::CollapsingHeader("Interaction (don`t work)")) {
                 ImGui::SliderFloat("##Interaction", &Interaction, 0, 100);
             }*/

            ImGui::End();


            // Rendering
            ImGui::Render();





            // glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
             //glClear(GL_COLOR_BUFFER_BIT);








            glUniform1f(vTimeLocation, vTime);//+
            glUniform2f(vScreenSizeLocation, display_w, display_h);//+
            glUniform3f(vColorBackgroundLocation, 0.0f, 0.0f, 0.0f);//+
            glUniform3fv(vColorLocation, 18, color);//+
            glUniform3fv(vRotationLocation, 9, Rotation);//+
            glUniform1fv(vAudioLocation, 3, Audio);
            glUniform1fv(vReactLocation, 3, React);
            glUniform2fv(vInteractionPointLocation, 2, InteractionPoint);
            glUniform1f(vInteractionLocation, Interaction);
            glDrawArrays(GL_QUADS, 0, 4);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    };

    void UpdateShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
        unsigned static int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        static int success;
        static char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        }
        // fragment shader
        unsigned static int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        }
        // link shaders
        unsigned static int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        static float f = 1.0f;
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        static float vertices[] = {
           -1.0f, -1.0f, 0.0f,
           -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
        };



        unsigned static int VBO, VAO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        vScreenSizeLocation = glGetUniformLocation(shaderProgram, "vScreenSize");
        vTimeLocation = glGetUniformLocation(shaderProgram, "vTime");
        vColorBackgroundLocation = glGetUniformLocation(shaderProgram, "vColorBackground");
        vColorLocation = glGetUniformLocation(shaderProgram, "vColor");
        vRotationLocation = glGetUniformLocation(shaderProgram, "vRotation");
        vAudioLocation = glGetUniformLocation(shaderProgram, "vAudio");
        vReactLocation = glGetUniformLocation(shaderProgram, "vReact");
        vInteractionPointLocation = glGetUniformLocation(shaderProgram, "vInteractionPoint");
        vInteractionLocation = glGetUniformLocation(shaderProgram, "vInteraction");
        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(shaderProgram);
    }

    ~APP() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    };




};