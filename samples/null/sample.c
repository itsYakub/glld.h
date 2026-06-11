#define GLLD_VERBOSE
#define GLLD_NO_EXTENSIONS
#define GLLD_IMPLEMENTATION
#include "./../../glld.h"


int main(void) {
    if (!glldLoadGL()) { return (1); }

    /* ... */

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* ... */

    return (0);
}
