/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  glld.h: OpenGL API Loader:
 *
 *      - made by: <<glld-author>>
 *      - version: <<glld-version>>
 *      - licence: <<glld-licence>>
 *
 *
 *  OpenGL settings:
 *      - profile: <<glld-glprofile>>
 *      - version: <<glld-glversion>> (OpenGL)
 *      - version: <<glld-glesversion>> (OpenGL ES)
 *      - version: <<glld-glscversion>> (OpenGL SC)
 *
 *
 *  Configuration (can be defined by user):
 *
 *      #define GLLD_IMPLEMENTATION
 *          - TYPE:
 *              MANDATORY
 *          - DESCRIPTION:
 *              Embed the implementation section of the library into the source file.
 *              NOTE:
 *                  This should be defined only once in the entire codebase.
 *                  Otherwise, defining this option will cause a multiple-definitions error.
 *
 *      #define GLLD_GLX
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of GLX for context loading.
 *              NOTE:
 *                  glld.h doesn't load GLX dynamically. For this flag to work you must
 *                  link your program with GLX library (libGLX.so: -lGLX).
 *
 *      #define GLLD_EGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of EGL for context loading.
 *              NOTE:
 *                  glld.h doesn't load EGL dynamically. For this flag to work you must
 *                  link your program with EGL library (libEGL.so: -lEGL).
 *
 *      #define GLLD_WGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of Windows's WGL for context loading.
 *              NOTE:
 *                  glld.h doesn't load WGL dynamically. For this flag to work you must
 *                  link your program with WGL library (Windows GDI: -lgdi32) (OpenGL32.dll: -lopengl32).
 *
 *      #define GLLD_DLSYM
 *          - TYPE:
 *              OPTIONAL (DEFINED BY DEFAULT) 
 *          - DESCRIPTION:
 *              Default, platform-independent option for loading OpenGL. Defined by default.
 *              NOTE:
 *                  This solution may require the linkage with dynamic linking library.
 *                  For unix-based system it would be: libdl, -ldl.
 *                  For win32 system: Kernel32.dll.
 *
 *      #define GLLD_VERBOSE
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info/warning/error logging to standard-output/standard-error.
 *  
 *      #define GLLD_VERBOSE_INFO
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info-logging to standard-output/standard-error.
 *              Enabled by default if GLLD_VERBOSE is defined.
 *
 *      #define GLLD_VERBOSE_WARN
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables warning-logging to standard-output/standard-error.
 *              Enabled by default if GLLD_VERBOSE is defined.
 *
 *      #define GLLD_VERBOSE_ERROR
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables error-logging to standard-output/standard-error.
 *              Enabled by default if GLLD_VERBOSE is defined.
 *
 *      #define GLLD_EXTENSIONS
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enable OpenGL extensions (default script should define this option).
 *
 *      #define GLLD_NO_EXTENSIONS
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Disable OpenGL extensions.
 *
 *
 *  Constants (MUST NOT be defined by user):
 *
 *      GLLD_PLATFORM
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Name of the platform glld.h is used on as a string, compile detected.
 *
 *      GLLD_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Current version of glld.h header file as a string.
 *
 *      GLLD_GL_PROFILE
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default profile of OpenGL and OpenGLES handled by glld.h.
 *
 *      GLLD_GL_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGL handled by glld.h.
 *
 *      GLLD_GLES_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGLES handled by glld.h.
 *
 *      GLLD_GLSC_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGLSC handled by glld.h.
 *
 *      GL_VERSION_...
 *          - TYPE:
 *              Integer
 *          - DESCRIPTION:
 *              Compile-time version detection of OpenGL.
 *
 *
 *  Summary and Notes:
 *
 *      This is glld.h: single-header only OpenGL loader for Windows, MacOS and Linux systems.
 *      The goal of this library is simple: provide users with drag-n-drop solution for loading
 *      legacy and modern OpenGL and OpenGLES functions.
 *
 *      glld.h is generated based on the OpenGL Registry, hosted by KhronosGroup.
 *      Generator is made in python3 on GNU/Linux platform. It works with latest python3 versios.
 *      Source:
 *      - https://github.com/KhronosGroup/OpenGL-Registry.git
 *
 *      This project is heavily inspired by the following projects:
 *      - nothings/stb: https://github.com/nothings/stb.git
 *      - Dav1dde/glad: https://github.com/Dav1dde/glad.git
 *      - macron/glbind: https://github.com/mackron/glbind.git
 *
 *      Cheers,
 *          <<glld-author>>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_glld_h_)
# define _glld_h_ 1
#
# if defined (__gl_h_)
#  error "#include <GL/gl.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_h_ */
# define __gl_h_ 1
#
# if defined (__gl_glext_h_)
#  error "#include <GL/glext.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_glext_h_ */
# define __gl_glext_h_ 1
#
# if defined (__gl_glcorearb_h_)
#  error "#include <GL/glcorearb.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_glcorearb_h_ */
# define __gl_glcorearb_h_ 1
#
# if defined (__gles2_gl2_h_)
#  error "#include <GLES2/gl2.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles2_gl2_h_ */
# define __gles2_gl2_h_ 1
#
# if defined (__gles2_gl2ext_h_)
#  error "#include <GLES2/gl2ext.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles2_gl2ext_h_ */
# define __gles2_gl2ext_h_ 1
#
# if defined (__gl2platform_h_)
#  error "#include <GLES2/gl2platform.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl2platform_h_ */
# define __gl2platform_h_ 1
#
# if defined (__gles3_gl3_h_)
#  error "#include <GLES3/gl3.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles3_gl3_h_ */
# define __gles3_gl3_h_ 1
#
# if defined (__gles3_gl31_h_)
#  error "#include <GLES3/gl31.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles3_gl31_h_ */
# define __gles3_gl31_h_ 1
#
# if defined (__gles3_gl32_h_)
#  error "#include <GLES3/gl32.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles3_gl32_h_ */
# define __gles3_gl32_h_ 1
#
# if defined (__gles3_gl3ext_h_)
#  error "#include <GLES3/gl3ext.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gles3_gl3ext_h_ */
# define __gles3_gl3ext_h_ 1
#
# if defined (__gl3platform_h_)
#  error "#include <GLES3/gl3platform.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl3platform_h_ */
# define __gl3platform_h_ 1
#
#  if !defined (__cplusplus)
#   include <stdio.h>
#   include <stdint.h>
#   include <stddef.h>
#   include <assert.h>
#  else
#   include <cstdio>
#   include <cstdint>
#   include <cstddef>
#   include <cassert>
#   include <string>
#  endif /* __cplusplus */
#
# if defined (__cplusplus)

extern "C" {

# endif /* __cplusplus */
#
# if defined (_WIN32) && !defined (APIENTRY) && !defined (__CYGWIN__) && !defined (__SCITECH_SNAP__)
#  if !defined (WIN32_LEAN_AND_MEAN)
#   define WIN32_LEAN_AND_MEAN 1
#  endif /* WIN32_LEAN_AND_MEAN */
#  include <windows.h>
# endif /* _WIN32, APIENTRY, __CYGWIN__, __SCITECH_SNAP__ */
#
# if !defined (APIENTRY)
#  define APIENTRY
# endif /* APIENTRY */
# if !defined (APIENTRYP)
#  define APIENTRYP APIENTRY *
# endif /* APIENTRYP */
# if !defined (GLAPI)
#  define GLAPI extern
# endif /* GLAPI */
#
# /* Define platform macros */
# if defined (__linux__)
#  define GLLD_PLATFORM "linux"
#  define GLLD_PLATFORM_LINUX 1
#
# elif defined (__APPLE__) || defined (__MACH__)
#  define GLLD_PLATFORM "apple"
#  define GLLD_PLATFORM_APPLE 1
#
# elif defined (__CYGWIN__) || defined (_WIN32)
#  define GLLD_PLATFORM "win32"
#  define GLLD_PLATFORM_WIN32 1
#
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
#  define GLLD_PLATFORM "bsd"
#  define GLLD_PLATFORM_BSD 1
#
# else
#  error /* No valid platform found */
# endif
#
# if !defined GLLD_VERSION
#  define GLLD_VERSION "<<glld-version>>"
# endif
#
/* <<glld-macro-glprofile>> */
#
/* <<glld-macro-glversion>> */
#
<<glld-macro-ext-state>>

/* SECTION: glld */

typedef void *(*t_glldLoader) (const char *);

GLAPI int glldLoadGL(void);

GLAPI int glldUnloadGL(void);

GLAPI int glldLoadGLLoader(t_glldLoader);

GLAPI void *glldGetProcAddress(const char *);

/* SECTION: OpenGL */

<<glld-macro-version-list>>
#
<<glld-macro-ext-list>>
#
<<glld-type-declr>>

<<glld-enum-declr>>
<<glld-func-ptr>>
<<glld-func-declr-1>>
<<glld-func-declr-2>>
#
# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLLD_IMPLEMENTATION)
#
#  if defined (GLLD_PLATFORM_LINUX) || defined (GLLD_PLATFORM_APPLE) || defined (GLLD_PLATFORM_BSD)
#   include <dlfcn.h>
#  endif
#
#  if defined (GLLD_PLATFORM_WIN32)
#   include <libloaderapi.h>
#  endif
#
#  if defined (GLLD_GLX)
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif
#
#  if defined (GLLD_EGL)
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#  endif
#
#  if defined (GLLD_WGL)
#   include <wingdi.h>
#  endif
#
#  if defined (GLLD_VERBOSE)
#   define GLLD_VERBOSE_INFO 1
#   define GLLD_VERBOSE_WARN 1
#   define GLLD_VERBOSE_ERROR 1
#  endif
#
#  if defined (__cplusplus)

extern "C" {

#  endif /* __cplusplus */
    
/* SECTION: globals */

struct s_nameaddr {

#  if !defined (__cplusplus)
    const char          *name;
#  else
    const std::string   &name;
#  endif /* __cplusplus */

    void        **addr;
};

/* key-value pair array of OpenGL functions */
static struct s_nameaddr    g_nameaddr[] = {
    
<<glld-func-nameaddr>>

    /* ... */

    { "", 0 }
};

/* handle to libGL.so / libGL.dll */ 
static void *g_handle = 0;

/* SECTION:
 *  glld API
 * * * * * * * * * * */

GLAPI int glldLoadGL(void) {

#  if defined (GLLD_GLX)
    return (glldLoadGLLoader((t_glldLoader) glXGetProcAddress));
#  endif /* GLLD_GLX */
#  if defined (GLLD_EGL)
    return (glldLoadGLLoader((t_glldLoader) eglGetProcAddress));
#  endif /* GLLD_EGL */
#  if defined (GLLD_WGL)
    return (glldLoadGLLoader((t_glldLoader) wglGetProcAddress));
#  endif /* GLLD_WGL */

    return (glldLoadGLLoader((t_glldLoader) glldGetProcAddress));

}


GLAPI int glldUnloadGL(void) {
    if (g_handle) {

#  if defined (GLLD_PLATFORM_LINUX) || defined (GLLD_PLATFORM_APPLE)
        dlclose(g_handle), g_handle = 0;
#  endif /* GLLD_PLATFORM_LINUX, GLLD_PLATFORM_APPLE */
#  if defined (GLLD_PLATFORM_WIN32)
        FreeLibrary(g_handle), g_handle = 0;
#  endif /* GLLD_PLATFORM_WIN32 */

    }

    return (1);
}


GLAPI int glldLoadGLLoader(t_glldLoader load) {
    if (!load) { return (0); }
    for (size_t i = 0; g_nameaddr[i].addr; i++) {
        /* If the function is already loaded, skip it... */
        if (*g_nameaddr[i].addr) { continue; }

#  if !defined (__cplusplus)
        *g_nameaddr[i].addr = load(g_nameaddr[i].name);
#  else
        *g_nameaddr[i].addr = load(g_nameaddr[i].name.c_str());
#  endif /* __cplusplus */

        if (!*g_nameaddr[i].addr) { return (0); }
    }

    return (1);
}


GLAPI void *glldGetProcAddress(const char *name) {
    const char *names[] = {

#  if defined (GLLD_PLATFORM_LINUX)
        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0
#  endif /* GLLD_PLATFORM_LINUX */
#  if defined (GLLD_PLATFORM_APPLE)
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0
#  endif /* GLLD_PLATFORM_APPLE */
#  if defined (GLLD_PLATFORM_WIN32)
        "opengl32.dll",
        0
#  endif /* GLLD_PLATFORM_WIN32 */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {

#  if defined (GLLD_PLATFORM_LINUX) || defined (GLLD_PLATFORM_APPLE)
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
#  endif /* GLLD_PLATFORM_LINUX, GLLD_PLATFORM_APPLE */
#  if defined (GLLD_PLATFORM_WIN32)
            g_handle = LoadLibraryA(names[i]);
#  endif /* GLLD_PLATFORM_WIN32 */

        }

        if (!g_handle) {

#  if defined (GLLD_VERBOSE_ERROR)
            fprintf(stderr, "glld.h: could not load an OpenGL handle.\n");
#  endif /* GLLD_VERBOSE_ERROR */

            return (0);

        }
    }

#  if defined (GLLD_PLATFORM_LINUX) || defined (GLLD_PLATFORM_APPLE)
    void proc = dlsym(g_handle, name);
#  endif /* GLLD_PLATFORM_LINUX, GLLD_PLATFORM_APPLE */
#  if defined (GLLD_PLATFORM_WIN32)
    void proc = GetProcAddress(g_handle, name);
#  endif /* GLLD_PLATFORM_WIN32 */

    if (!proc) {

#  if defined (GLLD_VERBOSE_ERROR)
        fprintf(stderr, "glld.h: could not load a procedure: %s\n", name);
#  endif /* GLLD_VERBOSE_ERROR */
    
        return (0);
    }
    return (proc);
}

/* SECTION: OpenGL */

<<glld-func-declr-0>>
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* GLLD_IMPLEMENTATION */
#endif /* _glld_h_ */
