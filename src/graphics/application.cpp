#include "application.h"

// Application Object Constructor with predefined window size, title and predefined shaders (for now)
Application::Application() : renderer("shader.vs", "shader.fs"), texture("dvd.png"){
    
    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[] = {
        
        // Positions        // Colors         // Texture Uv
         0.2f,  0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.2f,  0.2f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f 
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    renderer.set_vbo(vertices, sizeof(vertices));
    renderer.set_ebo(indices,  sizeof(indices));

    // Set Postion, Color and Texture Uv Attributes (note this for loop only works if all attributes are GL_FLOAT and have 3 elements)
    renderer.set_attribute(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    renderer.set_attribute(1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
    renderer.set_attribute(2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));

}

// Loop until the user closes the application
void Application::run(){

    float xoffset=0;
    float yoffset=0;

    float xcount= 0.005;
    float ycount= 0.008;

    while(!window.shouldClose()){    
        window.processInput();

        renderer.set_uniform_float("xoffset", xoffset);
        renderer.set_uniform_float("yoffset", yoffset);

        texture.bind();
        renderer.set_uniform_int("u_Texture", 0);

        xoffset += xcount;
        yoffset += ycount;

        if(xoffset >= 0.8 | xoffset <= -0.8) xcount *= -1;
        if(yoffset >= 0.8 | yoffset <= -0.8) ycount *= -1;


        renderer.clear();
        renderer.draw();

        window.swapBuffers();
        window.pollEvents();
    }
}