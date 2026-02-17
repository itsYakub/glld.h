/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  gload.h: OpenGL API Loader:
 *
 *      - made by: <<gload-author>>
 *      - version: <<gload-version>>
 *      - licence: <<gload-licence>>
 *
 *
 *  OpenGL settings:
 *      - profile: <<gload-glprofile>>
 *      - version: <<gload-glversion>> (OpenGL)
 *      - version: <<gload-glesversion>> (OpenGL ES)
 *      - version: <<gload-glscversion>> (OpenGL SC)
 *
 *
 *  Configuration (can be defined by user):
 *
 *      #define GLOAD_IMPLEMENTATION
 *          - TYPE:
 *              MANDATORY
 *          - DESCRIPTION:
 *              Embed the implementation section of the library into the source file.
 *              NOTE:
 *                  This should be defined only once in the entire codebase.
 *                  Otherwise, defining this option will cause a multiple-definitions error.
 *
 *      #define GLOAD_GLX
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of GLX for context loading.
 *              NOTE:
 *                  gload.h doesn't load GLX dynamically. For this flag to work you must
 *                  link your program with GLX library (libGLX.so: -lGLX).
 *
 *      #define GLOAD_EGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of EGL for context loading.
 *              NOTE:
 *                  gload.h doesn't load EGL dynamically. For this flag to work you must
 *                  link your program with EGL library (libEGL.so: -lEGL).
 *
 *      #define GLOAD_WGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of Windows's WGL for context loading.
 *              NOTE:
 *                  gload.h doesn't load WGL dynamically. For this flag to work you must
 *                  link your program with WGL library (Windows GDI: -lgdi32) (OpenGL32.dll: -lopengl32).
 *
 *      #define GLOAD_DLSYM
 *          - TYPE:
 *              OPTIONAL (DEFINED BY DEFAULT) 
 *          - DESCRIPTION:
 *              Default, platform-independent option for loading OpenGL. Defined by default.
 *              NOTE:
 *                  This solution may require the linkage with dynamic linking library.
 *                  For unix-based system it would be: libdl, -ldl.
 *                  For win32 system: Kernel32.dll.
 *
 *      #define GLOAD_VERBOSE
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info/warning/error logging to standard-output/standard-error.
 *  
 *      #define GLOAD_VERBOSE_INFO
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
 *
 *      #define GLOAD_VERBOSE_WARN
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables warning-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
 *
 *      #define GLOAD_VERBOSE_ERROR
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables error-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
 *
 *      #define GLOAD_EXTENSIONS
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enable OpenGL extensions (default script should define this option).
 *
 *      #define GLOAD_NO_EXTENSIONS
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Disable OpenGL extensions.
 *
 *
 *  Constants (MUST NOT be defined by user):
 *
 *      GLOAD_PLATFORM
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Name of the platform gload.h is used on as a string, compile detected.
 *
 *      GLOAD_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Current version of gload.h header file as a string.
 *
 *      GLOAD_GL_PROFILE
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default profile of OpenGL and OpenGLES handled by gload.h.
 *
 *      GLOAD_GL_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGL handled by gload.h.
 *
 *      GLOAD_GLES_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGLES handled by gload.h.
 *
 *      GLOAD_GLSC_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Default version of OpenGLSC handled by gload.h.
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
 *      This is gload.h: single-header only OpenGL loader for Windows, MacOS and Linux systems.
 *      The goal of this library is simple: provide users with drag-n-drop solution for loading
 *      legacy and modern OpenGL and OpenGLES functions.
 *
 *      gload.h is generated based on the OpenGL Registry, hosted by KhronosGroup.
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
 *          <<gload-author>>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_gload_h_)
# define _gload_h_ 1
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
#  define GLOAD_LINUX 1
#  define GLOAD_PLATFORM "linux"
# endif /* __linux__ */
# if defined (__APPLE__)
#  define GLOAD_APPLE 1
#  define GLOAD_PLATFORM "apple"
# endif /* __APPLE__ */
# if defined (_WIN32)
#  define GLOAD_WIN32 1
#  define GLOAD_PLATFORM "win32"
# endif /* _WIN32 */
# if !defined (GLOAD_LINUX) && !defined (GLOAD_APPLE) && !defined (GLOAD_WIN32)
#  error "Unrecognized platform. Neither GNU/Linux, nor Apple, nor Win32 platforms were detected."
# endif /* GLOAD_LINUX, GLOAD_APPLE, GLOAD_WIN32 */
#
# if !defined GLOAD_VERSION
#  define GLOAD_VERSION "<<gload-version>>"
# endif /* GLOAD_VERSION */
#
/* <<gload-macro-glprofile>> */
#
/* <<gload-macro-glversion>> */
#
/* <<gload-macro-ext-state>> */

/* SECTION:
 *  gload API
 * * * * * * * * * * */

typedef void    *(*t_gloadLoader)(const char *);

/* `gloadLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * `gloadLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGL(void);

/* `gloadLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `gloadGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadUnloadGL(void);

/* `gloadLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * gloadLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and gload.h provides a built-in solution: `gloadGetProcAddress`.
 *
 * - param: `t_gloadLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGLLoader(t_gloadLoader);

/* `gloadGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * - param: `const char *name` - name of the symbol
 * - returns: address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *);

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<gload-macro-version-list>> */
#
/* <<gload-macro-ext-list>> */
#
/* <<gload-type-declr>> */

/* <<gload-enum-declr>> */
/* <<gload-func-ptr>> */
/* <<gload-func-declr-1>> */
/* <<gload-func-declr-2>> */
#
# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLOAD_IMPLEMENTATION)
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
#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
#   include <dlfcn.h>
#  endif /* GLOAD_LINUX, GLOAD_APPLE*/
#  if defined (GLOAD_WIN32)
#   include <libloaderapi.h>
#  endif /* GLOAD_WIN32 */
#
#  if !defined (GLOAD_DLSYM) && !(defined (GLOAD_GLX) || defined (GLOAD_EGL) || defined (GLOAD_WGL))
#   define GLOAD_DLSYM 1
#  endif /* GLOAD_DLSYM, GLOAD_GLX, GLOAD_EGL, GLOAD_WGL */
#
#  if defined (GLOAD_DLSYM)
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_GLX."
#   endif /* GLOAD_GLX */
#   if defined (GLOAD_EGL)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_EGL."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#  endif /* GLOAD_DLSYM */
#
#  if defined (GLOAD_GLX)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_EGL)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_EGL."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif /* GLOAD_GLX */
#
#  if defined (GLOAD_EGL)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_GLX."
#   endif /* GLOAD_GLX */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#  endif /* GLOAD_EGL */
#
#  if defined (GLOAD_WGL)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_GLX."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <wingdi.h>
#  endif /* GLOAD_WGL */
#
#  if defined (GLOAD_VERBOSE)
#   define GLOAD_VERBOSE_INFO 1
#   define GLOAD_VERBOSE_WARN 1
#   define GLOAD_VERBOSE_ERROR 1
#  endif /* GLOAD_VERBOSE */
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
    
/* <<gload-func-nameaddr>> */

    /* null-terminator */
    { "", 0 }
};

/* `static void *g_handle` - handle to shared/dynamic library.
 * */
static void *g_handle = 0;

/* SECTION:
 *  gload API
 * * * * * * * * * * */

/* `gloadLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * `gloadLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGL(void) {

#  if defined (GLOAD_GLX)
    return (gloadLoadGLLoader((t_gloadLoader) glXGetProcAddress));
#  endif /* GLOAD_GLX */
#  if defined (GLOAD_EGL)
    return (gloadLoadGLLoader((t_gloadLoader) eglGetProcAddress));
#  endif /* GLOAD_EGL */
#  if defined (GLOAD_WGL)
    return (gloadLoadGLLoader((t_gloadLoader) wglGetProcAddress));
#  endif /* GLOAD_WGL */
#  if defined (GLOAD_DLSYM)
    return (gloadLoadGLLoader((t_gloadLoader) gloadGetProcAddress));
#  endif /* GLOAD_DLSYM */

}

/* `gloadLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `gloadGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * - returns: `true` on success, `false` on failure.
 * */
GLAPI int   gloadUnloadGL(void) {
    if (g_handle) {

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
        dlclose(g_handle), g_handle = 0;
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
        FreeLibrary(g_handle), g_handle = 0;
#  endif /* GLOAD_WIN32 */

    }

    return (1);
}

/* `gloadLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.2) loading process.
 * 
 * gloadLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and gload.h provides a built-in solution: `gloadGetProcAddress`.
 *
 * - param: `t_gloadLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGLLoader(t_gloadLoader load) {
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

/* `gloadGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * - param: `const char *name` - name of the symbol
 * - return: address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *name) {
    void        *proc;
    const char  *names[] = {

#  if defined (GLOAD_LINUX)
        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0
#  endif /* GLOAD_LINUX */
#  if defined (GLOAD_APPLE)
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0
#  endif /* GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
        "opengl32.dll",
        0
#  endif /* GLOAD_WIN32 */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
            g_handle = LoadLibraryA(names[i]);
#  endif /* GLOAD_WIN32 */

        }

        if (!g_handle) {

#  if defined (GLOAD_VERBOSE_ERROR)
            fprintf(stderr, "gload.h: could not load an OpenGL handle.\n");
#  endif /* GLOAD_VERBOSE_ERROR */

            return (0);

        }
    }

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
    proc = dlsym(g_handle, name);
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
    proc = GetProcAddress(g_handle, name);
#  endif /* GLOAD_WIN32 */

    if (!proc) {

#  if defined (GLOAD_VERBOSE_ERROR)
            fprintf(stderr, "gload.h: could not load a procedure: %s\n", name);
#  endif /* GLOAD_VERBOSE_ERROR */
    
            return (0);
    }
    return (proc);
}

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<gload-func-declr-0>> */
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* OPENGL_IMPLEMENTATION */
#endif /* _gload_h_ */
