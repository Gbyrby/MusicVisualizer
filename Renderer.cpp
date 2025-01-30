#pragma once
#include "Renderer.h"
#include "FileSystem.h"

#include <vector>
#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
Renderer::Renderer() {

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw ("GLFW is not initialized");
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        throw "Not have a window";
    glfwMakeContextCurrent(window);

    glewInit();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();

    // Настройка флагов напрямую в конструкторе
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Включаем навигацию с клавиатуры
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    show_demo_window = false;

#ifdef DEBUG
    show_demo_window = true;
#endif // DEBUG


    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glfwSwapInterval(1); // Enable vsync
    
    std::string vertexShaderString = FileSystem::ReadFile("ShaderCode/VertexShaders/VertexShader.txt");
    std::string fragmentShaderString = FileSystem::ReadFile("ShaderCode/FragmentShaders/YandexBlob.txt");

    const char* vertexShaderText = vertexShaderString.c_str();
    const char* fragmentShaderText = fragmentShaderString.c_str();
    this->UpdateShaders(vertexShaderText, fragmentShaderText);
}

Renderer::~Renderer(){
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::UpdateShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
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
        std::cout << "glCompileShader(vertexShader)" << infoLog << std::endl;
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
        std::cout << "glCompileShader(fragmentShader)" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "glLinkProgram(shaderProgram)" << infoLog << std::endl;
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



void Renderer::Draw(std::vector<double>& AudioData)
{
    glfwSwapInterval(1);
    WindowShouldClose = glfwWindowShouldClose(window);

    // Main loop
    
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        
        
        


        

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            
            static int counter = 0;

            ImGui::Begin("Settings!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::Text("Time %.3f", glfwGetTime()-1);
            ImGui::Text("vector size %i", AudioData.size()); 
            if (ImGui::Button("Play/Pause Music"))
            {
                play = !play;
                //glfwSetTime(1.0f);
            }

            if (ImGui::CollapsingHeader("Uniform settings")) {
                if (ImGui::TreeNode("Color")) {


                    ImGui::ColorEdit3("##MyColor##1", (float*)&color[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::SameLine();
                    ImGui::ColorEdit3("##MyColor##2", (float*)&color[3], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::SameLine();
                    ImGui::ColorEdit3("##MyColor##3", (float*)&color[6], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::ColorEdit3("##MyColor##4", (float*)&color[9], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::SameLine();
                    ImGui::ColorEdit3("##MyColor##5", (float*)&color[12], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::SameLine();
                    ImGui::ColorEdit3("##MyColor##6", (float*)&color[15], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
                    ImGui::TreePop();
                };
                if (ImGui::TreeNode("Rotation")) {
                    ImGui::SliderFloat3("Rotation1", Rotation, 0, 1);
                    ImGui::SliderFloat3("Rotation2", &Rotation[3], 0, 1);
                    ImGui::SliderFloat3("Rotation3", &Rotation[6], 0, 1);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Audio")) {
                    ImGui::SliderFloat3("Audio", Audio, 0, 3);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("React")) {
                    ImGui::SliderFloat3("React", React, 0, 1);
                    ImGui::TreePop();
                }
                /* if (ImGui::CollapsingHeader("InteractionPoint (don`t work)")) {
                        ImGui::SliderFloat2("InteractionPoint", InteractionPoint, -1, 1);
                    }
                    if (ImGui::CollapsingHeader("Interaction (don`t work)")) {
                        ImGui::SliderFloat("##Interaction", &Interaction, 0, 100);
                    }*/
            }


            // Display some text (you can use a format strings too)
            ImGui::Checkbox("Use FFT", &UseFFT);
            ImGui::Checkbox("Use Smooth", &UseSmooth);
            ImGui::Checkbox("Show Lines", &ShowLines);
            //ImGui::SliderFloat("float", &f1, 0.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderInt("Smooth Step", &smoothStep, 1, 120);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderInt("Segment Lenght", &segmentLenght, 128, 4096);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Sensitivity", &sensitivity, 0.f, 2.f);
            //ImGui::SliderInt("int2", &i2, 0, 50);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::SliderInt("int3", &i3, 0, 1000);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
            ImGui::End();
        }

        


        
        
        float bass = 0;
        float medium = 0;
        float high = 0;

        for (int i = 0;i < AudioData.size() / 16;i++) {
            //if(bass> AudioData[i] / (AudioData.size() / 16))
            bass += AudioData[i] / (AudioData.size() / 16);
        }

        for (int i = AudioData.size() / 16;i < AudioData.size() / 8;i++) {   
            if(medium < AudioData[i] )
            medium = AudioData[i];
        }

        for (int i = AudioData.size() / 8;i < AudioData.size()/2;i++) {
            if(high < AudioData[i])
            high = AudioData[i];
        }
        /*for (int i = AudioData.size() / 16;i < AudioData.size() / 8;i++) {
           
                medium += AudioData[i] / ((AudioData.size() / 8) - (AudioData.size() / 16));
        }

        for (int i = AudioData.size() / 8;i < AudioData.size() / 2;i++) {
        
                high += AudioData[i] / (AudioData.size() / 2 - (AudioData.size() / 8));
        }*/

        bass *= sensitivity/5;
        medium *= sensitivity/10;
        high *= sensitivity/10;


        if (play) {
            Audio[0] = bass / 5;
            Audio[1] = medium/2;
            Audio[2] = high;
            React[0] = bass / 25;
            React[1] = medium / 5;
            React[2] = high / 5;
        }
        //std::cout << "bass:" << bass << " medium:" << medium << " high:" << high << std::endl;


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //glClearColor(FFTData[i1]/f1 * clear_color.w, FFTData[i2]/f1 * clear_color.w, FFTData[i3]/f1 * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
        glUseProgram(shaderProgram);
        //glLoadIdentity(); // загрузить идентичную матрицу
        glUniform1f(vTimeLocation, glfwGetTime());//+
        glUniform2f(vScreenSizeLocation, display_w / (100 / 100), display_h / (100 / 100));//+
        glUniform3f(vColorBackgroundLocation, 0.0f, 0.0f, 0.0f);//+
        glUniform3fv(vColorLocation, 18, color);//+
        glUniform3fv(vRotationLocation, 9, Rotation);//+
        glUniform1fv(vAudioLocation, 3, Audio);
        glUniform1fv(vReactLocation, 3, React);
        glUniform2fv(vInteractionPointLocation, 2, InteractionPoint);
        glUniform1f(vInteractionLocation, Interaction);
        glDrawArrays(GL_QUADS, 0, 4);

        if (ShowLines) {
            glUseProgram(0);
            //main line
            glBegin(GL_LINE_STRIP);
            glColor3f(1, 0, 1);
            for (size_t i = 0;i < AudioData.size();i++) {
                glVertex3f((i * (1. / AudioData.size() * 2) - 1.) * 0.75, AudioData[i] / 100. - 0.0, 0);
            }
            glEnd();

            //Uniform Audio to shader

            glBegin(GL_LINE_STRIP);
            glColor3f(1, 1, 1);
            glVertex3f((0 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[0] / 100. - 0.0, 0);
            glVertex3f((AudioData.size() / 16 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[0] / 100. - 0.0, 0);
            glVertex3f((AudioData.size() / 16 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[1] / 100. - 0.0, 0);
            glVertex3f((AudioData.size() / 8 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[1] / 100. - 0.0, 0);
            glVertex3f((AudioData.size() / 8 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[2] / 100. - 0.0, 0);
            glVertex3f((AudioData.size() / 2 * (1. / AudioData.size() * 2) - 1.) * 0.75, Audio[2] / 100. - 0.0, 0);
            glEnd();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        
    }
    //std::cout << FFTData.size()<< std::endl;
}
