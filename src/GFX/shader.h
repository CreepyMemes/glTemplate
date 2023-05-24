#pragma once

#include "gfx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Defining OS dependant executable's absolute path retrieval
#ifdef _WIN32
    #include <io.h>
    #define getExecutablePath(buf, size) _fullpath((buf), _pgmptr, (size))
#else
    #include <unistd.h>
    #define getExecutablePath(buf, size) readlink("/proc/self/exe", (buf), (size))
#endif

class Shader{

    public:
        Shader(const std::string& vertexFileName, const std::string& fragmentFileName);
        ~Shader();

        void use();

        void setBool (const std::string& name, bool  value);        
        void setInt  (const std::string& name, int   value);
        void setFloat(const std::string& name, float value);

    private:
        GLuint handle;

        std::string getShaderPath(const std::string& fileName);
        std::string getParentPath(const std::string& path);
        std::string getSource(const std::string& shaderPath);

        GLint getUniformLocation(const std::string& name);


        GLuint CompileShader(const GLuint type, const char* source);
        GLuint createShader(const GLuint vertex, const GLuint fragment);
};