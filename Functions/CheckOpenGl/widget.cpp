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
#include <QLayout>
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
//    setFixedSize(QSize(400, 120));

    QVBoxLayout* pLayout = new QVBoxLayout();//水平布局

    m_CSlabel = new QLabel(this);
    m_openGLlabel = new QLabel(this);
    m_BSFlabel = new QLabel(this);
    m_GLUlabel = new QLabel(this);

    pLayout->addWidget(m_CSlabel);
    pLayout->addWidget(m_openGLlabel);
    pLayout->addWidget(m_BSFlabel);
    pLayout->addWidget(m_GLUlabel);

    this->setLayout(pLayout);

    getOpenGLVersion();
    m_CSlabel->setText(m_Changshang);
    m_openGLlabel->setText(m_OpenGlVersion);
    m_BSFlabel->setText(m_Biaoshifu);
    m_GLUlabel->setText(m_GLUVersion);

}

Widget::~Widget()
{

}

void Widget::getOpenGLVersion()
{
    QString strChangshang = "OpenGl实现厂商名 : ";
    QString strOpenGlrVersion = "OpenGLVersion : ";
    QString strBiaoshifu = "渲染器标识符 : ";
    QString strGLUVersion = "GLU工具库版本 : ";

//    // 方法1  ：  在项目中该方式出现获取的opengl版本号不正确的情况
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


//    const GLubyte * name = glGetString(GL_VENDOR);
//    strChangshang += QString((char*)name);

//    const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
//    strOpenGlrVersion += QString((char*)OpenGLVersion);

//    const GLubyte * biaoshifu = glGetString(GL_RENDERER);
//    strBiaoshifu += QString((char*)biaoshifu);

//    const GLubyte * gluVersion = gluGetString(GLU_VERSION);
//    strGLUVersion += QString((char*)gluVersion);

//    wglDeleteContext(ourOpenGLRenderingContext);
//    ReleaseDC(NULL, ourWindowHandleToDeviceContext);

//    m_Changshang = strChangshang;
//    m_OpenGlVersion = strOpenGlrVersion;
//    m_Biaoshifu = strBiaoshifu;
//    m_GLUVersion = strGLUVersion;


    // 方法2

    int wnd = glutCreateWindow("OpenGL Version");

    const GLubyte * name = glGetString(GL_VENDOR);
    strChangshang += QString((char*)name);

    const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
    strOpenGlrVersion += QString((char*)OpenGLVersion);

    const GLubyte * biaoshifu = glGetString(GL_RENDERER);
    strBiaoshifu += QString((char*)biaoshifu);

    const GLubyte * gluVersion = gluGetString(GLU_VERSION);
    strGLUVersion += QString((char*)gluVersion);

    glutDestroyWindow(wnd);


    m_Changshang = strChangshang;
    m_OpenGlVersion = strOpenGlrVersion;
    m_Biaoshifu = strBiaoshifu;
    m_GLUVersion = strGLUVersion;
}
