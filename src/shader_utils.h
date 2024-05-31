#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <string>

std::string readFile(const char* filePath);
unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource);

#endif
