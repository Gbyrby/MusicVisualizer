//#define TIMEOUT
#define TIMEOUT_TIME 10

#include "App.h"



// Main code
int main(int, char**)
{   
    
   

    
    std::string vertexShaderString = FileSystem::ReadFile("ShaderCode/VertexShaders/VertexShader.txt");
    std::string fragmentShaderString = FileSystem::ReadFile("ShaderCode/FragmentShaders/YandexBlob.txt");
    const char* vertexShaderText = vertexShaderString.c_str();
    const char* fragmentShaderText = fragmentShaderString.c_str();
    //std::cout << vertexShaderString;

    APP app(1280,720);
    app.UpdateShaders(vertexShaderText, fragmentShaderText);
    app.MainLoop();
    

    return 0;
}
