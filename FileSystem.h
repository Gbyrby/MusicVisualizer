#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
class FileSystem {
public:

    static std::string ReadFile(const char* path) {
        std::fstream file;
        std::string outputText;
        file.open(path);

        if (!file.is_open()) {
            std::cout << "Error of opening file:" << path << std::endl;
        }

        std::stringstream file_stringstream;
        file_stringstream << file.rdbuf();
        outputText = file_stringstream.str();
        file.close();

        return outputText;
    }
    void GetFiles(const char* Directory) {
    }
};