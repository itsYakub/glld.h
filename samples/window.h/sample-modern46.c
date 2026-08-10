#define GLLD_IMPLEMENTATION
#include "./../../glld.h"
#
#define WINDOW_IMPLEMENTATION
#include <window/window.h>



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
    /* initialize window.h */
    library_t library = 0;
    win_init(&library);

    /* set API to 'WINDOW_API_OPENGL' */
    win_set_hints(library, WINDOW_CLIENT_API, WINDOW_API_OPENGL);

    /* create window */
    window_t window = 0;
    win_window_create(library, &window, 800, 600, "glld.h - window.h sample");
    win_window_map(library, window);

    /* create context */
    context_t context = 0;
    win_context_create(library, &context, window);
    win_gl_make_current(library, context);

    /* load OpenGL */
    if (!glld_loader((glld_loader_t) win_gl_get_proc_address)) { return (1); }
    

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
                
    GLuint vbo, ibo;
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ibo);
    
    glNamedBufferData(vbo, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);
    glNamedBufferData(ibo, sizeof(g_indices), g_indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat));

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(GLfloat));
    glVertexArrayElementBuffer(vao, ibo);


    for (int exit = 0; !exit; ) {
        /* render */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        /* poll events */
        win_gl_swap_buffers(library, context);
        event_t event = { 0 };
        while (win_event_poll(library, &event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    exit = 1;
                } break;

                case (WINDOW_EVENT_WINDOW_RESIZE): {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                } break;
            }
        }
    }
   

    glDeleteBuffers(1, &vbo), vbo = 0;
    glDeleteBuffers(1, &ibo), ibo = 0;
    glDeleteVertexArrays(1, &vao), vao = 0;
    glDeleteProgram(shader), shader = 0;

    /* quit */
    win_quit(library);
    return (0);
}
