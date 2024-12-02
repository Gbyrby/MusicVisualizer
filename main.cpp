#include "App.h"




// Main code
int main(int, char**)
{   
    std::fstream file;
    file.open("ShaderCode/FragmentShaders/YandexBlob.txt");
    std::stringstream file_stringstream;
   
    file_stringstream << file.rdbuf();

    
    std::string fragmentShaderText;
    fragmentShaderText = file_stringstream.str();
    const char* fragmentShaderSource = fragmentShaderText.c_str();
    file.close();

    std::fstream file1;
    file1.open("ShaderCode/VertexShaders/VertexShader.txt");
    std::stringstream file_stringstream1;
    file_stringstream1 << file1.rdbuf();

    file1.close();
    std::string vertexShaderText;
    vertexShaderText = file_stringstream1.str();
    const char* vertexShaderSource = vertexShaderText.c_str();


    APP app(vertexShaderSource, fragmentShaderSource);
    app.MainLoop();
    

    return 0;
}
