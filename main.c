#define ASSERT(x) if (!(x)) *((int *)0)
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "win32_gl.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftlcdfil.h>
#include <freetype/ftmodapi.h>
#include <freetype/ftadvanc.h>
#include <freetype/ftglyph.h>
#include <freetype/ftdriver.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;

    float s0;
    float t0;
    float s1;
    float t1;
} glyph_data_t;

#pragma pack(push, 1)
typedef struct {
    float x;
    float y;

    float s;
    float t;
} vertex_t;
#pragma pack(pop)

LRESULT CALLBACK win32_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if(uMsg == WM_CLOSE) {
        exit(0);
    } else {
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return result;
}

static void project_ortho(float l, float r, float t, float b, float n, float f, float *ortho)
{
    memset(ortho, 0, sizeof(float)*4*4);
    ortho[0*4 + 0] = 2.0f/(r-l);
    ortho[1*4 + 1] = 2.0f/(t-b);
    ortho[2*4 + 2] = -2.0f/(f-n);
    ortho[3*4 + 0] = -(r+l)/(r-l);
    ortho[3*4 + 1] = -(t+b)/(t-b);
    ortho[3*4 + 2] = -(f+n)/(f-n);
    ortho[3*4 + 3] = 1.0f;
}

int WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmdl_string, int show_code)
{
    HWND wnd_handle;
    HGLRC gl_ctx;
    HDC dc;

    FT_Library ft_lib; 
    FT_UInt interp_ver = TT_INTERPRETER_VERSION_40; 
    FT_Face ft_face;

    uint32_t atlas;
    int atlas_w;
    int atlas_h;

    int run = 1;

    char text[] = "Hello_World!";
    int glyph_count = sizeof(text) - 1;
    glyph_data_t glyphs[sizeof(text) - 1];

    int i;
    int x;

    int ascender;
    int descender;

    int wnd_w = 800;
    int wnd_h = 600;

    if(!win32_make_gl_window("Demo", wnd_w, wnd_h, 32, 24, 8, win32_proc, &wnd_handle, &gl_ctx, &dc)) {
        return 1;
    }

    win32_load_ogl_exts();

    //
    // Init FreeType 
    //
    
    FT_Init_FreeType(&ft_lib); 
    FT_Property_Set(ft_lib, "truetype", "interp-version", &interp_ver); 
    FT_Library_SetLcdFilter(ft_lib, FT_LCD_FILTER_DEFAULT); 

    // Loading font from a file
    FT_New_Face(ft_lib, "c:\\windows\\fonts\\consola.ttf", 0, &ft_face);
    FT_Set_Pixel_Sizes(ft_face, 0, 49);

    ascender  = ft_face->size->metrics.ascender  >> 6;
    descender = ft_face->size->metrics.descender >> 6;


    //
    // Creatig altas
    //

    glGenTextures(1, &atlas);
    glBindTexture(GL_TEXTURE_2D, atlas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    atlas_w = 1024;
    atlas_h = 1024;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlas_w, atlas_h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
    //
    // Rendering & Uploading glyphs to the atlas
    //
    x = 0;
    for(i = 0; i < glyph_count; ++i) {
        FT_UInt glyph_index;

        glyph_index = FT_Get_Char_Index(ft_face, text[i]);
        FT_Load_Glyph(ft_face, glyph_index, FT_LOAD_TARGET_LCD);
        FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_LCD);

        glyphs[i].x = ft_face->glyph->bitmap_left;
        glyphs[i].y = ft_face->glyph->bitmap_top;
        glyphs[i].w = ft_face->glyph->bitmap.width/3;
        glyphs[i].h = ft_face->glyph->bitmap.rows;
        glyphs[i].s0 = (float)x/(float)atlas_w;
        glyphs[i].t0 = 0.0f;
        glyphs[i].s1 = (float)(x + glyphs[i].w)/(float)atlas_w;
        glyphs[i].t1 = (float)glyphs[i].h/(float)atlas_h;

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, glyphs[i].w, glyphs[i].h, GL_RGB, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);

        x += glyphs[i].w + 2;
    }
    
    ShowWindow(wnd_handle, SW_SHOWNORMAL); 

#if 1
    //
    // Fixed function pipeline
    //
    while(run) {
        MSG msg;
        float ortho[16];
        int y;

        memset(&msg, 0, sizeof(msg));
        if(GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glViewport(0, 0, wnd_w, wnd_h);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        project_ortho(0.0f, (float)wnd_w, 0.0f, (float)wnd_h, -10.0f, 10.0f, (float *)ortho);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf((float *)ortho);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glUseProgram(0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, atlas);

        glEnable(GL_BLEND);
        glBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
        glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        x = 200;
        y = 200; 

        for(i = 0; i < glyph_count; ++i) {
            float x0, x1, y0, y1;

            glBegin(GL_QUADS);

            x0 = (float)(int)(((float)x + (float)glyphs[i].x) + 0.375f);
            y0 = (float)(int)((float)y + 0.375f);
            x1 = (float)(int)((float)x + (float)glyphs[i].w + (float)glyphs[i].x + 0.375f);
            y1 = (float)(int)((float)y + (float)glyphs[i].h + 0.375f);

            y0 += ascender - glyphs[i].y - descender;
            y1 += ascender - glyphs[i].y - descender;

            glTexCoord2f(glyphs[i].s0, glyphs[i].t0);
            glVertex2f(x0, y0);

            glTexCoord2f(glyphs[i].s0, glyphs[i].t1);
            glVertex2f(x0, y1);

            glTexCoord2f(glyphs[i].s1, glyphs[i].t1);
            glVertex2f(x1, y1);

            glTexCoord2f(glyphs[i].s1, glyphs[i].t0);
            glVertex2f(x1, y0);
            glEnd();

            x += glyphs[i].w;
        }

        SwapBuffers(dc);
    }
#else
    //
    // Programmable Pipeline
    //
    
    {
        static char vertex_shader[] = {
            "#version 130\n"
                "uniform mat4 u_proj;\n"
                "in vec2  in_pos;\n"
                "in vec2  in_uv;\n"
                "smooth out vec2 v_uv;\n"
                "smooth out vec2 v_pos;\n"
                "void main(void)\n"
                "{\n"
                "v_uv    = in_uv;\n"
                "v_pos   = in_pos;\n"
                "gl_Position = u_proj*vec4(in_pos.x, in_pos.y, 0.0f, 1.0);\n"
                "}"
        };

        static char fragment_shader[] = {
            "#version 130\n"
                "uniform sampler2D u_atlas;\n"
                "uniform vec3 u_text_color;\n"
                "smooth in vec2  v_uv;\n"
                "smooth in vec2  v_pos;\n"
                "out vec4 src_color0;\n"
                "out vec4 src_color1;\n"
                "void main(void)\n"
                "{\n"
                "float f;\n"
                "vec4 tex_px;\n"
                "tex_px.rgb = texture2D(u_atlas, v_uv).rgb;\n"
                "tex_px.a   = (tex_px.r + tex_px.g + tex_px.b);\n"
                "if(tex_px.a > 0.0f) {\n"
                "tex_px.a = 1.0f;\n"
                "}\n"
                "src_color0 = vec4(u_text_color.r, u_text_color.g, u_text_color.b, 1.0f);\n"
                "src_color1 = vec4(tex_px.r, tex_px.g, tex_px.b, tex_px.a);\n"
                "}"
        };

        uint32_t vbo;
        uint32_t ibo;

        vertex_t *vertices;
        uint32_t *indices;

        uint32_t color = 0x000000;
        float pos_x = 200.0f;
        float pos_y = 200.0f;

        uint32_t program;
        uint32_t u_handle;

        float ortho[16];

        vertices = (vertex_t *)malloc(sizeof(vertex_t)*4*glyph_count);
        indices  = (uint32_t *)malloc(sizeof(uint32_t)*6*glyph_count);

        for (i = 0; i < glyph_count; ++i) {
            // Top left
            vertices[4*i + 0].x = pos_x;
            vertices[4*i + 0].y = pos_y + ascender - glyphs[i].y - descender;
            vertices[4*i + 0].s = glyphs[i].s0;
            vertices[4*i + 0].t = glyphs[i].t0;
            // Bottom left
            vertices[4*i + 1].x = pos_x;
            vertices[4*i + 1].y = pos_y + glyphs[i].h + ascender - glyphs[i].y - descender;
            vertices[4*i + 1].s = glyphs[i].s0;
            vertices[4*i + 1].t = glyphs[i].t1;
            // Bottom right
            vertices[4*i + 2].x = pos_x + glyphs[i].w;
            vertices[4*i + 2].y = pos_y + glyphs[i].h + ascender - glyphs[i].y - descender;
            vertices[4*i + 2].s = glyphs[i].s1;
            vertices[4*i + 2].t = glyphs[i].t1;
            // Top right
            vertices[4*i + 3].x = pos_x + glyphs[i].w;
            vertices[4*i + 3].y = pos_y + ascender - glyphs[i].y - descender;
            vertices[4*i + 3].s = glyphs[i].s1;
            vertices[4*i + 3].t = glyphs[i].t0;

            indices[6*i + 0] = 4*i + 0;
            indices[6*i + 1] = 4*i + 1;
            indices[6*i + 2] = 4*i + 3;
            indices[6*i + 3] = 4*i + 3;
            indices[6*i + 4] = 4*i + 1;
            indices[6*i + 5] = 4*i + 2;

            pos_x += glyphs[i].w;
        }

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t)*4*glyph_count, vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*6*glyph_count, indices, GL_STATIC_DRAW);

        program = glCreateProgram();
        {
            uint32_t shader;
            int compiled;
            int size = sizeof(vertex_shader);

            const char *v[1];

            v[0] = vertex_shader;
            shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(shader, 1, v, &size);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if(!compiled) {
                exit(1);
            }
            glAttachShader(program, shader);

            v[0] = fragment_shader;
            size = sizeof(fragment_shader);
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(shader, 1, v, &size);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if(!compiled) {
                exit(1);
            }
            glAttachShader(program, shader);

            glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &compiled);
            if(!compiled) {
                exit(1);
            }
        }
        glBindFragDataLocationIndexed(program, 0, 0, "src_color0");
        glBindFragDataLocationIndexed(program, 1, 0, "src_color1");

        glUseProgram(program);
        
        u_handle = glGetUniformLocation(program, "u_proj");
        project_ortho(0.0f, (float)wnd_w, 0.0f, (float)wnd_h, -10.0f, 10.0f, (float *)ortho);
        glUniformMatrix4fv(u_handle, 1, GL_FALSE, ortho);

        u_handle = glGetUniformLocation(program, "u_text_color");
        glUniform3f(u_handle, 0.0f, 0.0f, 0.0f); // Text color

        u_handle = glGetUniformLocation(program, "u_atlas");
        glUniform1i(u_handle, 0);

        while(run) {
            MSG msg;

            memset(&msg, 0, sizeof(msg));
            if(GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            glViewport(0, 0, wnd_w, wnd_h);
            glClearColor(1, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, atlas);

            
            glUseProgram(program);

            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(vertex_t), 0);
            glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(vertex_t), (void *)(sizeof(float)*2));

            glDrawElements(GL_TRIANGLES, glyph_count*6, GL_UNSIGNED_INT, NULL);

            SwapBuffers(dc);
        }
    }
#endif

    return 0;
}
