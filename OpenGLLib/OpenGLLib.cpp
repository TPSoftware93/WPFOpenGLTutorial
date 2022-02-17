#include "framework.h"
#include "OpenGLLib.h"
#include "gl/gl.h"
#include <iostream>

int* InitOpenglContext(int* windowHandle)
{
    std::cout << "Init" << std::endl;
    PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
    1,                     // version number  
    PFD_DRAW_TO_WINDOW |   // support window  
    PFD_SUPPORT_OPENGL |   // support OpenGL  
    PFD_DOUBLEBUFFER,      // double buffered  
    PFD_TYPE_RGBA,         // RGBA type  
    24,                    // 24-bit color depth  
    0, 0, 0, 0, 0, 0,      // color bits ignored  
    0,                     // no alpha buffer  
    0,                     // shift bit ignored  
    0,                     // no accumulation buffer  
    0, 0, 0, 0,            // accum bits ignored  
    32,                    // 32-bit z-buffer  
    0,                     // no stencil buffer  
    0,                     // no auxiliary buffer  
    PFD_MAIN_PLANE,        // main layer  
    0,                     // reserved  
    0, 0, 0                // layer masks ignored  
    };
    HDC  hdc;
    int  iPixelFormat;

    hdc = GetDC((HWND)windowHandle);
    std::cout << "Get DC" << std::endl;
    iPixelFormat = ChoosePixelFormat(hdc, &pfd);
    std::cout << "Get DC" << std::endl;
    SetPixelFormat(hdc, iPixelFormat, &pfd);
    std::cout << "Get DC" << std::endl;
    HGLRC glContext = wglCreateContext(hdc);
    std::cout << "Get DC" << std::endl;
    if (glContext) {
        std::cout << "Get DC" << std::endl;
        wglMakeCurrent(hdc, glContext);
        std::cout << "Get DC" << std::endl;
    }
    ReleaseDC((HWND)windowHandle, hdc);
    return (int*)(glContext);
}
void Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void ClearColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}
void ResizeViewport(int startX, int startY, int width, int height)
{
    glViewport(startX, startY, width, height);
}
void SwapWindowBuffers(int* windowHandler)
{
    HDC hdc = GetDC((HWND)windowHandler);
    SwapBuffers(hdc);
    ReleaseDC((HWND)windowHandler, hdc);
}
float rotation = 0;
void DrawTriangle(float r, float g, float b) {
    glLoadIdentity();
    glRotatef(rotation, 0, 0, 1);
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();
    rotation +=0.1f;
}

void GetString(char* string,int lenght)
{
    strcpy_s(string,lenght,(const char*)glGetString(GL_VERSION));
}
