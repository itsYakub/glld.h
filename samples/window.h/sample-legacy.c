#define GLLD_IMPLEMENTATION
#include "./../../glld.h"
#
#define WINDOW_IMPLEMENTATION
#include <window/window.h>

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

    for (int exit = 0; !exit; ) {
        /* render */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();

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

    /* quit */
    win_quit(library);
    return (0);
}
