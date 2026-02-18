#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <GLFW/glfw3.h>



int main(void) {
    if (!glfwInit()) { return (1); }

    GLFWwindow *window = glfwCreateWindow(800, 600, "glld.h - GLFW3 sample", 0, 0);
    if (!window) { return (1); }

    glfwMakeContextCurrent(window);

    if (!glldLoadGLLoader((t_glldLoader) glfwGetProcAddress)) { return (1); }


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return (0);
}
