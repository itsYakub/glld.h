#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <GLFW/glfw3.h>



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


GLfloat g_vertices[] = {
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0,
     0.5, -0.5, 0.0,
     0.5,  0.5, 0.0
};


GLuint  g_indices[] = {
    0, 1, 2,
    1, 2, 3
};



int main(void) {
    if (!glfwInit()) { return (1); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "glld.h - GLFW3 sample", 0, 0);
    if (!window) { return (1); }

    glfwMakeContextCurrent(window);

    if (!glld_loader((glld_loader_t) glfwGetProcAddress)) { return (1); }


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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo, ibo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) (0 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteBuffers(1, &vbo), vbo = 0;
    glDeleteBuffers(1, &ibo), ibo = 0;
    glDeleteVertexArrays(1, &vao), vao = 0;
    glDeleteProgram(shader), shader = 0;

    glfwTerminate();
    return (0);
}
