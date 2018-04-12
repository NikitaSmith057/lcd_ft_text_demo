#ifndef _WIN32_GL_H_
#define _WIN32_GL_H_

#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include <gl/glcorearb.h>

#ifndef MEMSET
#define MEMSET(ptr, val, size)     memset(ptr, val, size)
#endif

#ifndef MEMCPY
#define MEMCPY(ptr_a, ptr_b, size) memcpy(ptr_a, ptr_b, size);
#endif

static HMODULE ogl_instance;

#pragma warning (disable : /* Data ptr to func ptr cast */ 4055 4054)

#define WIN32_LOAD_GL_EXT(E, F) ((F) = ((E)__win32_load_gl_ext((#F))))
static void * __win32_load_gl_ext(char *func_name)
{
    void *func_ptr = (void *) wglGetProcAddress(func_name);

    if(func_ptr  == (void *) 0 ||
            (func_ptr == (void *) 0x1) ||
            (func_ptr == (void *) 0x2) ||
            (func_ptr == (void *) 0x3)) {
        func_ptr = (void *) GetProcAddress(ogl_instance, func_name);
    }

    return func_ptr;
}

#define OPENGL_PROCS_LIST                                               \
OPENGL_LOAD_FUNC(PFNGLACTIVETEXTUREPROC, glActiveTexture)           \
OPENGL_LOAD_FUNC(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D) \
OPENGL_LOAD_FUNC(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit)       \
OPENGL_LOAD_FUNC(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv) \
OPENGL_LOAD_FUNC(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample) \
OPENGL_LOAD_FUNC(PFNGLGETSHADERIVPROC, glGetShaderiv)               \
OPENGL_LOAD_FUNC(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog) \
OPENGL_LOAD_FUNC(PFNGLGETPROGRAMIVPROC, glGetProgramiv)             \
OPENGL_LOAD_FUNC(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)   \
OPENGL_LOAD_FUNC(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation) \
OPENGL_LOAD_FUNC(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)     \
OPENGL_LOAD_FUNC(PFNGLUNIFORM1IPROC, glUniform1i)                   \
OPENGL_LOAD_FUNC(PFNGLUNIFORM1FPROC, glUniform1f)                   \
OPENGL_LOAD_FUNC(PFNGLUNIFORM2FPROC, glUniform2f)                   \
OPENGL_LOAD_FUNC(PFNGLUNIFORM3FPROC, glUniform3f)                   \
OPENGL_LOAD_FUNC(PFNGLUNIFORM4FPROC, glUniform4f)                   \
OPENGL_LOAD_FUNC(PFNGLUNIFORM3FVPROC, glUniform3fv)                 \
OPENGL_LOAD_FUNC(PFNGLUNIFORM3UIPROC, glUniform3ui)                 \
OPENGL_LOAD_FUNC(PFNGLUNIFORM4UIPROC, glUniform4ui)                 \
OPENGL_LOAD_FUNC(PFNGLSHADERSOURCEPROC, glShaderSource)             \
OPENGL_LOAD_FUNC(PFNGLCREATESHADERPROC, glCreateShader)             \
OPENGL_LOAD_FUNC(PFNGLCOMPILESHADERPROC, glCompileShader)           \
OPENGL_LOAD_FUNC(PFNGLDELETESHADERPROC, glDeleteShader)             \
OPENGL_LOAD_FUNC(PFNGLATTACHSHADERPROC, glAttachShader)             \
OPENGL_LOAD_FUNC(PFNGLCREATEPROGRAMPROC, glCreateProgram)           \
OPENGL_LOAD_FUNC(PFNGLDELETEPROGRAMPROC, glDeleteProgram)           \
OPENGL_LOAD_FUNC(PFNGLLINKPROGRAMPROC, glLinkProgram)               \
OPENGL_LOAD_FUNC(PFNGLUSEPROGRAMPROC, glUseProgram)                 \
OPENGL_LOAD_FUNC(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders) \
OPENGL_LOAD_FUNC(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation) \
OPENGL_LOAD_FUNC(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv) \
OPENGL_LOAD_FUNC(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv) \
OPENGL_LOAD_FUNC(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName) \
OPENGL_LOAD_FUNC(PFNGLBLENDEQUATIONPROC, glBlendEquation)           \
OPENGL_LOAD_FUNC(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)       \
OPENGL_LOAD_FUNC(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)       \
OPENGL_LOAD_FUNC(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer) \
OPENGL_LOAD_FUNC(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D) \
OPENGL_LOAD_FUNC(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus) \
OPENGL_LOAD_FUNC(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)       \
OPENGL_LOAD_FUNC(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)       \
OPENGL_LOAD_FUNC(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
OPENGL_LOAD_FUNC(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer) \
OPENGL_LOAD_FUNC(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer) \
OPENGL_LOAD_FUNC(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray) \
OPENGL_LOAD_FUNC(PFNGLGENBUFFERSPROC, glGenBuffers)                 \
OPENGL_LOAD_FUNC(PFNGLBINDBUFFERPROC, glBindBuffer)                 \
OPENGL_LOAD_FUNC(PFNGLBUFFERDATAPROC, glBufferData)                 \
OPENGL_LOAD_FUNC(PFNGLBUFFERSUBDATAPROC, glBufferSubData)           \
OPENGL_LOAD_FUNC(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays) \
OPENGL_LOAD_FUNC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)           \
OPENGL_LOAD_FUNC(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers)     \
OPENGL_LOAD_FUNC(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer)     \
OPENGL_LOAD_FUNC(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage) \
OPENGL_LOAD_FUNC(PFNGLDRAWBUFFERSPROC, glDrawBuffers)               \
OPENGL_LOAD_FUNC(PFNGLMAPBUFFERPROC, glMapBuffer)                   \
OPENGL_LOAD_FUNC(PFNGLUNMAPBUFFERPROC, glUnmapBuffer)               \
OPENGL_LOAD_FUNC(PFNGLUNMAPNAMEDBUFFERPROC, glUnmapNamedBuffer)     \
OPENGL_LOAD_FUNC(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange)         \
OPENGL_LOAD_FUNC(PFNGLFRAMEBUFFERTEXTUREPROC, glFramebufferTexture) \
OPENGL_LOAD_FUNC(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData)     \
OPENGL_LOAD_FUNC(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers) \
OPENGL_LOAD_FUNC(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange)       \
OPENGL_LOAD_FUNC(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor) \
OPENGL_LOAD_FUNC(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced) \
OPENGL_LOAD_FUNC(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv) \
OPENGL_LOAD_FUNC(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer)       \
OPENGL_LOAD_FUNC(PFNGLPRIMITIVERESTARTINDEXPROC, glPrimitiveRestartIndex) \
OPENGL_LOAD_FUNC(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate)   \
OPENGL_LOAD_FUNC(PFNGLDRAWELEMENTSBASEVERTEXPROC, glDrawElementsBaseVertex) \
OPENGL_LOAD_FUNC(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC, glDrawElementsInstancedBaseVertex) \
OPENGL_LOAD_FUNC(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced) \
OPENGL_LOAD_FUNC(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample) \
OPENGL_LOAD_FUNC(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer) \
OPENGL_LOAD_FUNC(PFNGLBLENDCOLORPROC, glBlendColor)                 \
OPENGL_LOAD_FUNC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB) \
OPENGL_LOAD_FUNC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB) \
OPENGL_LOAD_FUNC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT) \
OPENGL_LOAD_FUNC(PFNGLBINDRENDERBUFFERPROC, glBindRenderBuffer)     \
OPENGL_LOAD_FUNC(PFNGLGENRENDERBUFFERSPROC, glGenRenderBuffers)     \
OPENGL_LOAD_FUNC(PFNGLRENDERBUFFERSTORAGEPROC, glRenderBufferStorage) \
OPENGL_LOAD_FUNC(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC, glBindFragDataLocationIndexed) \
OPENGL_LOAD_FUNC(PFNGLADDSWAPHINTRECTWINPROC, glAddSwapHintRectWIN) \
OPENGL_LOAD_FUNC(PFNGLGETTEXTUREIMAGEPROC, glGetTextureImage) \
OPENGL_LOAD_FUNC(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback) \
OPENGL_LOAD_FUNC(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap) \
/* end */

#define OPENGL_LOAD_FUNC(type, name) type name;
OPENGL_PROCS_LIST
#undef OPENGL_LOAD_FUNC

static void win32_load_ogl_exts()
{
#define OPENGL_LOAD_FUNC(type, name) WIN32_LOAD_GL_EXT(type, name);
    OPENGL_PROCS_LIST
#undef OPENGL_LOAD_FUNC
}

typedef HGLRC WINAPI PFN_wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext,
        const int *attribList);

typedef BOOL WINAPI PFN_wglGetPixelFormatAttribivARB(HDC hdc,
        int iPixelFormat,
        int iLayerPlane,
        UINT nAttributes,
        const int *piAttributes,
        int *piValues);

typedef BOOL WINAPI PFN_wglChoosePixelFormatARB(HDC hdc,
        const int *piAttribIList,
        const FLOAT *pfAttribFList,
        UINT nMaxFormats,
        int *piFormats,
        UINT *nNumFormats);

typedef BOOL WINAPI PFN_wglGetPixelFormatAttribfvARB(HDC hdc,
        int iPixelFormat,
        int iLayerPlane,
        UINT nAttributes,
        const int *piAttributes,
        FLOAT *pfValues);

static BOOL win32_make_gl_window(LPCTSTR    title,
                                 DWORD      width, DWORD height,
                                 BYTE       bpp_count,
                                 BYTE       depth_bit_count,
                                 BYTE       stencil_bit_count,
                                 WNDPROC    proc,
                                 HWND   *   out_handle,
                                 HGLRC  *   out_glctx,
                                 HDC    *   out_dc)
{
    HINSTANCE instance = GetModuleHandle(NULL);
    HANDLE handle      = 0;
    HGLRC  glctx       = 0;
    HDC    dc          = 0;
    BOOL   done        = FALSE;
    WNDCLASS wnd_class;


    ogl_instance = LoadLibrary("opengl32.dll");
    if(!ogl_instance) {
        return FALSE;
    }

    MEMSET(&wnd_class, 0, sizeof(wnd_class));

    wnd_class.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wnd_class.lpfnWndProc   = proc;
    wnd_class.hInstance     = GetModuleHandle(NULL);
    wnd_class.lpszClassName = "win32_window_class_name";
    wnd_class.hIcon         = NULL;

    if(RegisterClassA(&wnd_class)) {
        RECT wnd_rect;

        int ext_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        int wnd_style = WS_OVERLAPPEDWINDOW;

        wnd_rect.left   = 0;
        wnd_rect.top    = 0;
        wnd_rect.right  = width;
        wnd_rect.bottom = height;
        AdjustWindowRectEx(&wnd_rect, wnd_style, 0, ext_style);

        width  = wnd_rect.right - wnd_rect.left;
        height = wnd_rect.bottom - wnd_rect.top;

        handle = CreateWindowEx(ext_style, wnd_class.lpszClassName,
                                title, wnd_style,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                width, height,
                                0, 0, instance, 0);

        if(handle) {
            PIXELFORMATDESCRIPTOR pxfmt_data;
            int pxfmt;
            UINT fmt_count;

            INT ctx_attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 0,
                WGL_CONTEXT_FLAGS_ARB,        0, //WGL_CONTEXT_DEBUG_BIT_ARB,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                0,
            };

            INT int_attribs[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                WGL_COLOR_BITS_ARB,     24,
                WGL_ALPHA_BITS_ARB,     8,
                WGL_DEPTH_BITS_ARB,     16,
                WGL_STENCIL_BITS_ARB,   0,
                WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
                WGL_SAMPLES_ARB,        0,
                0,
            };

#if 0
            switch(0) {
            case 2:
                int_attribs[19] = 2;
                break;
            case 4:
                int_attribs[19] = 4;
                break;
            case 9:
                int_attribs[19] = 8;
                break;
            }
#endif

            MEMSET(&pxfmt, 0, sizeof(pxfmt));
            pxfmt_data.nSize        = sizeof(pxfmt);
            pxfmt_data.nVersion     = 1;
            pxfmt_data.dwFlags      = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_SWAP_COPY;
            pxfmt_data.iPixelType   = PFD_TYPE_RGBA;
            pxfmt_data.cColorBits   = bpp_count;
            pxfmt_data.cDepthBits   = depth_bit_count;
            pxfmt_data.cStencilBits = stencil_bit_count;
            pxfmt_data.iLayerType   = PFD_MAIN_PLANE;

            dc = GetDC(handle);

            done = SetPixelFormat(dc, ChoosePixelFormat(dc, &pxfmt_data), &pxfmt_data);
            ASSERT(done);

            glctx = wglCreateContext(dc);
            ASSERT(glctx);

            done = wglMakeCurrent(dc, glctx);
            ASSERT(done);

            WIN32_LOAD_GL_EXT(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
            WIN32_LOAD_GL_EXT(PFNWGLCHOOSEPIXELFORMATARBPROC,    wglChoosePixelFormatARB);
            WIN32_LOAD_GL_EXT(PFNWGLSWAPINTERVALEXTPROC,         wglSwapIntervalEXT);

            // Cleaning up
            //

            done = wglMakeCurrent(NULL, NULL);
            ASSERT(done);

            done = wglDeleteContext(glctx);
            ASSERT(done);

            done = ReleaseDC(handle, dc);
            ASSERT(done);

            done = DestroyWindow(handle);
            ASSERT(done);

            // Creating usable OpenGL context.
            //

            handle = CreateWindowEx(ext_style, wnd_class.lpszClassName, title, wnd_style, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);
            ASSERT(handle);

            dc = GetDC(handle);
            ASSERT(dc);

            done = wglChoosePixelFormatARB(dc, int_attribs, 0, 1, &pxfmt, &fmt_count);
            if(!done || fmt_count == 0) {
                pxfmt = ChoosePixelFormat(dc, &pxfmt_data);
            }

            done = SetPixelFormat(dc, pxfmt, &pxfmt_data);
            ASSERT(done);

            glctx = wglCreateContextAttribsARB(dc, 0, ctx_attribs);
            ASSERT(glctx);

            done = wglMakeCurrent(dc, glctx);
            ASSERT(done);

            if(wglSwapIntervalEXT) {
                wglSwapIntervalEXT(0);
            }
        }
    }

    if(done) {
        *out_handle = handle;
        *out_glctx  = glctx;
        *out_dc     = dc;
    } else {
        UnregisterClassA("win32_window_class_name", instance);
    }

    return done;
}

#endif
