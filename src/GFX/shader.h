#ifndef SHADER_H
    #define SHADER_H
    
    #include "gfx.h"

    #include <string>
    #include <fstream>
    #include <sstream>
    #include <iostream>
 
    // Shader Program Object that reads the shader source files, compiles and links them
    class Shader{

        private:
            std::string vertexSource;
            std::string fragmentSource;

            // Function that reads the source files
            void readSource(const char* vertexPath, const char* fragmentPath);

            // Function to compile a shader (vertex shader or fragment shader depending on the argument passed)
            unsigned int CompileShader(unsigned int type, const char* source);

            // Create a Program object for by compiling and linking the Vertex Shader and Fragment Shader sources
            unsigned int createShader(const unsigned int vertex, const unsigned int fragment);

        public:
            // the program's ID
            unsigned int id;

            // Constructor reads and builds the shader
            Shader(const char* vertexPath, const char* fragmentPath);

            // Use/Activate the shader object
            void use();

            // Utility uniform functions
            void setBool (const std::string &name, bool  value) const;        
            void setInt  (const std::string &name, int   value) const;
            void setFloat(const std::string &name, float value) const;
    };

#endif