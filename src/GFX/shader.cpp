
#include "shader.h"

// Create a Program object for by compiling and linking the Vertex Shader and Fragment Shader sources
unsigned int Shader::createShader(const unsigned int vertex, const unsigned int fragment){
    
    // Creates a program object and returns it's ID
    unsigned int program = glCreateProgram();

    // Attach the compiled Vertex Shader Object and Fragment Shader Object to the Program Object and link them
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Validate the program
    glValidateProgram(program);

    // Delete the Vertex Shader object and the Fragment shader object because they've been linked to the Program object
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Return the program's object ID
    return program;
}

// Function that reads the source files
void Shader::readSource(const char* vertexPath, const char* fragmentPath){

    // Ensure ifstream objects can throw exceptions
    std::ifstream vertexFile, fragmentFile;
    vertexFile.exceptions   (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        // Open files
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        
        // Read the file's buffer contents into streams
        std::stringstream vertexStream, fragmentStream;
        vertexStream   << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        // Close the file handlers
        vertexFile.close();
        fragmentFile.close();

        // Convert stream into string
        vertexSource = vertexStream.str();
        fragmentSource = fragmentStream.str();
    }
    catch(std::ifstream::failure e){
        std::cerr << "ERROR: Failed to read a shader file\n" << std::endl;
    }
}

// Function to compile a shader (vertex shader or fragment shader depending on the argument passed)
unsigned int Shader::CompileShader(unsigned int type, const char* source){
    
    // Creates a shader object and returns it's ID
    unsigned int shader = glCreateShader(type);

    // Replaces the source code in a shader object
    glShaderSource(shader, 1, &source, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Error handling message
    int success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE){
        int length;           glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char infoLog[length]; glGetShaderInfoLog(shader, length, &length, infoLog);

        std::cerr << "ERROR: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader Failed to compile\n" << infoLog << std::endl;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Constructor reads and builds the shader
Shader::Shader(const char* vertexPath, const char* fragmentPath){
    
    // Read the source files from their paths in this class constructor arguments
    readSource(vertexPath, fragmentPath);

    // Compile the Vertex Shader and Fragment Shader from their source retrieved by readSource()
    unsigned int vertex   = CompileShader(GL_VERTEX_SHADER,   vertexSource.c_str());
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Create the Program Object and save it's ID
    id = createShader(vertex, fragment);
}

// Use/Activate the shader object
void Shader::use(){
    glUseProgram(id);
}

// Utility uniform functions
void Shader::setBool (const std::string &name, bool  value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt  (const std::string &name, int   value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}