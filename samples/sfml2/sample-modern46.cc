#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/ContextSettings.hpp>



static const GLchar *g_vertex_glsl =
"#version 330 core\n"
"\n"
"layout (location=0)\n"
"in vec3 a_pos;\n"
"\n"
"void main() {\n"
"   gl_Position = vec4(a_pos, 1.0);\n"
"}\n";


static const GLchar *g_fragment_glsl =
"#version 330 core\n"
"\n"
"out vec4 f_col;\n"
"\n"
"void main() {\n"
"   f_col = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";


static const std::vector<GLfloat> g_vertices {
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0,
     0.5, -0.5, 0.0,
     0.5,  0.5, 0.0
};


static const std::vector<GLuint> g_indices {
    0, 1, 2,
    1, 2, 3
};



int main(void) { 
    sf::ContextSettings settings;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.majorVersion = 4;
    settings.minorVersion = 6;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    sf::Window window(sf::VideoMode( { 800, 600 } ), "glld.h - SFML sample", sf::Style::Titlebar | sf::Style::Close, settings);

    if (!window.setActive()) { return (1); }
    if (!glld_load()) { return (1); }
    
    
    GLuint sh_v = glCreateShader(GL_VERTEX_SHADER);
    GLuint sh_f = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(sh_v, 1, &g_vertex_glsl, 0);
    glShaderSource(sh_f, 1, &g_fragment_glsl, 0);
    
    glCompileShader(sh_v);
    glCompileShader(sh_f);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, sh_v);
    glAttachShader(shader, sh_f);
    glLinkProgram(shader);

    glDeleteShader(sh_v), sh_v = 0;
    glDeleteShader(sh_f), sh_f = 0;
    

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ibo);
    
    GLuint vbo, ibo;
    glNamedBufferData(vbo, g_vertices.size() * sizeof(GLfloat), g_vertices.data(), GL_STATIC_DRAW);
    glNamedBufferData(ibo, g_indices.size() * sizeof(GLuint), g_indices.data(), GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat));

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(GLfloat));
    glVertexArrayElementBuffer(vao, ibo);


    while (window.isOpen()) { 
        sf::Event event = { };
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed): {
                    window.close();
                } break;

                default: { } break;
            }
        }


        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, g_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);


        window.display();
    }
    
    
    glDeleteBuffers(1, &vbo), vbo = 0;
    glDeleteBuffers(1, &ibo), ibo = 0;
    glDeleteVertexArrays(1, &vao), vao = 0;
    glDeleteProgram(shader), shader = 0;
    
    if (!glldUnloadGL()) { return (1); }

    return (0);
}
