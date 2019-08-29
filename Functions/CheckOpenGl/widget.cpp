/*******************************************************************************
** @file:     widget.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-9-19
** @version:
*******************************************************************************/

#include "widget.h"
#include <QOpenGLFunctions>
#include "glut.h"

#include <Windows.h>
#include <windowsx.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Dialog);
    setFixedSize(QSize(300, 40));
    m_label = new QLabel(this);

    QString version = getOpenGLVersion();
    m_label->setText("OpenGl version:" + QString("%1").arg(version));

}

Widget::~Widget()
{

}

QString Widget::getOpenGLVersion()
{
//    // 方法1  ：  在项目中该方式出现获取的opengl版本号不正确的情况
//    QString strVersion;
//    PIXELFORMATDESCRIPTOR pfd =
//    {
//        sizeof(PIXELFORMATDESCRIPTOR),
//        1,
//        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
//        PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
//        32,                        //Colordepth of the framebuffer.
//        0, 0, 0, 0, 0, 0,
//        0,
//        0,
//        0,
//        0, 0, 0, 0,
//        24,                        //Number of bits for the depthbuffer
//        8,                        //Number of bits for the stencilbuffer
//        0,                        //Number of Aux buffers in the framebuffer.
//        PFD_MAIN_PLANE,
//        0,
//        0, 0, 0
//    };
//    HDC ourWindowHandleToDeviceContext = GetDC(NULL);

//    int  letWindowsChooseThisPixelFormat;
//    letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
//    SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

//    HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
//    wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

//    const GLubyte * OpenGLVersion = glGetString(GL_VERSION);

//    strVersion = QString((char*)OpenGLVersion);

//    wglDeleteContext(ourOpenGLRenderingContext);
//    ReleaseDC(NULL, ourWindowHandleToDeviceContext);

//    return strVersion;


    // 方法2
    QString strVersion;
    int wnd = glutCreateWindow("OpenGL Version");
    const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
    strVersion = QString((char*)OpenGLVersion);

    glutDestroyWindow(wnd);


    return strVersion;
}
