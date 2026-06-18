#define GLLD_IMPLEMENTATION
#include "./../../glld.h"
#
#define WINDOW_API_OPENGL
#define WINDOW_IMPLEMENTATION
#include <window/window.h>



int main(void) {
    if (!winInit()) { return (1); }
    if (!winGLSetAttribute(WINDOW_GL_CONTEXT_MAJOR_VERSION, 1)) { return (1); }
    if (!winGLSetAttribute(WINDOW_GL_CONTEXT_MINOR_VERSION, 0)) { return (1); }
    if (!winGLSetAttribute(WINDOW_GL_CONTEXT_PROFILE_MASK, 2)) { return (1); }


    t_window window = 0;
    if (!winCreateWindow(&window, 800, 600, "glld.h - window.h sample", 0)) { return (1); }
    if (!window) { return (1); }


    t_glcontext context = 0;
    if (!winGLCreateContext(&context, window)) { return (1); }
    if (!context) { return (1); }


    if (!winGLMakeCurrent(context, window)) { return (1); }
    if (!winMapWindow(window)) { return (1); }
    if (!glldLoadGLLoader((t_glldLoader) winGLGetProcAddress)) { return (1); }


    for (int exit = 0; !exit; ) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();


        winGLSwapBuffers(context, window);

        t_event event = { 0 };
        while (winPollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): { exit = 1; } break;
            }
        }
    }


    winGLDestroyContext(context, window);
    winDestroyWindow(window);
    winQuit();
    return (0);
}
