/*******************************************************************************
** @file:     widget.h
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2018-9-19
** @version:
*******************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void getOpenGLVersion();
private:
    QLabel *m_CSlabel;
    QLabel *m_openGLlabel;
    QLabel *m_BSFlabel;
    QLabel *m_GLUlabel;

    QString m_Changshang = "";
    QString m_OpenGlVersion = "";
    QString m_Biaoshifu = "";
    QString m_GLUVersion = "";
};

#endif // WIDGET_H
