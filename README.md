<div align="center">

# glld.h - single-header only OpenGL loader

</div>

glld.h is a single-header only legacy, modern and embedded-systems OpenGL loader, based on the official KhronosGroup's OpenGL Registry.
It's simple, easy to use, highly configurable with support for GNU/Linux, MacOS and Windows Operating Systems.

## Usage

glld.h is designed to be simple drag-n-drop library for your common C/C++ projects. Simply include it in your project.
There's no need to link with any library, unless you explicitly specify one of 3 backends: GLX, EGL or WGL.

```c
#define GLLD_IMPLEMENTATION
#include "glld.h"

int main(void) {
    if (!glldLoadGL()) { return (1); }

    /* ... */
    
    glClearColor(1.0, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* ... */

    return (0);
}
```

## Credits

Credits for glld.h must be given where it's needed.
The whole project is based on:
- [KhronosGroup/OpenGL-Registry](https://github.com/KhronosGroup/OpenGL-Registry.git);

Huge inspiration for the project and giant help in it's design were:
- [nothings/stb](https://github.com/nothings/stb.git);
- [Dav1dde/glad](https://github.com/Dav1dde/glad.git);
- [macron/glbind](https://github.com/mackron/glbind.git);

## Licence

This project is licenced under [LGPL-3 Licence](./LICENCE).
