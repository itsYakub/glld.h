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
# if defined (__linux__)
#  define GLLD_LINUX 1
#  define GLLD_PLATFORM "linux"
# endif /* __linux__ */
# if defined (__APPLE__)
#  define GLLD_APPLE 1
#  define GLLD_PLATFORM "apple"
# endif /* __APPLE__ */
# if defined (_WIN32)
#  define GLLD_WIN32 1
#  define GLLD_PLATFORM "win32"
# endif /* _WIN32 */
# if !defined (GLLD_LINUX) && !defined (GLLD_APPLE) && !defined (GLLD_WIN32)
#  error "Unrecognized platform. Neither GNU/Linux, nor Apple, nor Win32 platforms were detected."
# endif /* GLLD_LINUX, GLLD_APPLE, GLLD_WIN32 */
#
# if !defined GLLD_VERSION
#  define GLLD_VERSION "<<glld-version>>"
# endif /* GLLD_VERSION */
#
/* <<glld-macro-glprofile>> */
#
/* <<glld-macro-glversion>> */
#
/* <<glld-macro-ext-state>> */

/* SECTION:
 *  glld API
 * * * * * * * * * * */

typedef void    *(*t_glldLoader)(const char *);

/* `glldLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * `glldLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   glldLoadGL(void);

/* `glldLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `glldGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   glldUnloadGL(void);

/* `glldLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * glldLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and glld.h provides a built-in solution: `glldGetProcAddress`.
 *
 * - param: `t_glldLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   glldLoadGLLoader(t_glldLoader);

/* `glldGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * - param: `const char *name` - name of the symbol
 * - returns: address of the symbol on success, null on failure
 * */
GLAPI void  *glldGetProcAddress(const char *);

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<glld-macro-version-list>> */
#
/* <<glld-macro-ext-list>> */
#
/* <<glld-type-declr>> */

/* <<glld-enum-declr>> */
/* <<glld-func-ptr>> */
/* <<glld-func-declr-1>> */
/* <<glld-func-declr-2>> */
#
# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLLD_IMPLEMENTATION)
#
#  if defined (GLLD_LINUX) || defined (GLLD_APPLE)
#   include <dlfcn.h>
#  endif /* GLLD_LINUX, GLLD_APPLE*/
#  if defined (GLLD_WIN32)
#   include <libloaderapi.h>
#  endif /* GLLD_WIN32 */
#
#  if !defined (GLLD_DLSYM) && !(defined (GLLD_GLX) || defined (GLLD_EGL) || defined (GLLD_WGL))
#   define GLLD_DLSYM 1
#  endif /* GLLD_DLSYM, GLLD_GLX, GLLD_EGL, GLLD_WGL */
#
#  if defined (GLLD_DLSYM)
#   if defined (GLLD_GLX)
#    error "Multiple backends selected: GLLD_DLSYM and GLLD_GLX."
#   endif /* GLLD_GLX */
#   if defined (GLLD_EGL)
#    error "Multiple backends selected: GLLD_DLSYM and GLLD_EGL."
#   endif /* GLLD_EGL */
#   if defined (GLLD_WGL)
#    error "Multiple backends selected: GLLD_DLSYM and GLLD_WGL."
#   endif /* GLLD_WGL */
#  endif /* GLLD_DLSYM */
#
#  if defined (GLLD_GLX)
#   if defined (GLLD_DLSYM)
#    error "Multiple backends selected: GLLD_GLX and GLLD_DLSYM."
#   endif /* GLLD_DLSYM */
#   if defined (GLLD_EGL)
#    error "Multiple backends selected: GLLD_GLX and GLLD_EGL."
#   endif /* GLLD_EGL */
#   if defined (GLLD_WGL)
#    error "Multiple backends selected: GLLD_GLX and GLLD_WGL."
#   endif /* GLLD_WGL */
#
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif /* GLLD_GLX */
#
#  if defined (GLLD_EGL)
#   if defined (GLLD_DLSYM)
#    error "Multiple backends selected: GLLD_EGL and GLLD_DLSYM."
#   endif /* GLLD_DLSYM */
#   if defined (GLLD_GLX)
#    error "Multiple backends selected: GLLD_EGL and GLLD_GLX."
#   endif /* GLLD_GLX */
#   if defined (GLLD_WGL)
#    error "Multiple backends selected: GLLD_EGL and GLLD_WGL."
#   endif /* GLLD_WGL */
#
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#  endif /* GLLD_EGL */
#
#  if defined (GLLD_WGL)
#   if defined (GLLD_DLSYM)
#    error "Multiple backends selected: GLLD_WGL and GLLD_DLSYM."
#   endif /* GLLD_DLSYM */
#   if defined (GLLD_GLX)
#    error "Multiple backends selected: GLLD_WGL and GLLD_GLX."
#   endif /* GLLD_EGL */
#   if defined (GLLD_WGL)
#    error "Multiple backends selected: GLLD_WGL and GLLD_WGL."
#   endif /* GLLD_WGL */
#
#   include <wingdi.h>
#  endif /* GLLD_WGL */
#
#  if defined (GLLD_VERBOSE)
#   define GLLD_VERBOSE_INFO 1
#   define GLLD_VERBOSE_WARN 1
#   define GLLD_VERBOSE_ERROR 1
#  endif /* GLLD_VERBOSE */
#
#  if defined (__cplusplus)

extern "C" {

#  endif /* __cplusplus */
    
/* SECTION:
 *  Global objects
 * * * * * * * * * * */

/* `struct s_nameaddr` - key-value-pair structure of proc. names and addresses.
 * */

struct s_nameaddr {

#  if !defined (__cplusplus)
    const char          *name;
#  else
    const std::string   &name;
#  endif /* __cplusplus */

    void        **addr;
};

/* `static struct s_nameaddr g_nameaddr` - array of s_nameaddr structures, null-terminated.
 * */

static struct s_nameaddr    g_nameaddr[] = {
    
/* <<glld-func-nameaddr>> */

    /* null-terminator */
    { "", 0 }
};

/* `static void *g_handle` - handle to shared/dynamic library.
 * */
static void *g_handle = 0;

/* SECTION:
 *  glld API
 * * * * * * * * * * */

/* `glldLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * `glldLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   glldLoadGL(void) {

#  if defined (GLLD_GLX)
    return (glldLoadGLLoader((t_glldLoader) glXGetProcAddress));
#  endif /* GLLD_GLX */
#  if defined (GLLD_EGL)
    return (glldLoadGLLoader((t_glldLoader) eglGetProcAddress));
#  endif /* GLLD_EGL */
#  if defined (GLLD_WGL)
    return (glldLoadGLLoader((t_glldLoader) wglGetProcAddress));
#  endif /* GLLD_WGL */
#  if defined (GLLD_DLSYM)
    return (glldLoadGLLoader((t_glldLoader) glldGetProcAddress));
#  endif /* GLLD_DLSYM */

}

/* `glldLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `glldGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * - returns: `true` on success, `false` on failure.
 * */
GLAPI int   glldUnloadGL(void) {
    if (g_handle) {

#  if defined (GLLD_LINUX) || defined (GLLD_APPLE)
        dlclose(g_handle), g_handle = 0;
#  endif /* GLLD_LINUX, GLLD_APPLE */
#  if defined (GLLD_WIN32)
        FreeLibrary(g_handle), g_handle = 0;
#  endif /* GLLD_WIN32 */

    }

    return (1);
}

/* `glldLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * glldLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and glld.h provides a built-in solution: `glldGetProcAddress`.
 *
 * - param: `t_glldLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   glldLoadGLLoader(t_glldLoader load) {
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

/* `glldGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * - param: `const char *name` - name of the symbol
 * - return: address of the symbol on success, null on failure
 * */
GLAPI void  *glldGetProcAddress(const char *name) {
    void        *proc;
    const char  *names[] = {

#  if defined (GLLD_LINUX)
        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0
#  endif /* GLLD_LINUX */
#  if defined (GLLD_APPLE)
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0
#  endif /* GLLD_APPLE */
#  if defined (GLLD_WIN32)
        "opengl32.dll",
        0
#  endif /* GLLD_WIN32 */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {

#  if defined (GLLD_LINUX) || defined (GLLD_APPLE)
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
#  endif /* GLLD_LINUX, GLLD_APPLE */
#  if defined (GLLD_WIN32)
            g_handle = LoadLibraryA(names[i]);
#  endif /* GLLD_WIN32 */

        }

        if (!g_handle) {

#  if defined (GLLD_VERBOSE_ERROR)
            fprintf(stderr, "glld.h: could not load an OpenGL handle.\n");
#  endif /* GLLD_VERBOSE_ERROR */

            return (0);

        }
    }

#  if defined (GLLD_LINUX) || defined (GLLD_APPLE)
    proc = dlsym(g_handle, name);
#  endif /* GLLD_LINUX, GLLD_APPLE */
#  if defined (GLLD_WIN32)
    proc = GetProcAddress(g_handle, name);
#  endif /* GLLD_WIN32 */

    if (!proc) {

#  if defined (GLLD_VERBOSE_ERROR)
            fprintf(stderr, "glld.h: could not load a procedure: %s\n", name);
#  endif /* GLLD_VERBOSE_ERROR */
    
            return (0);
    }
    return (proc);
}

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<glld-func-declr-0>> */
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* GLLD_IMPLEMENTATION */
#endif /* _glld_h_ */
