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
    QString getOpenGLVersion();
private:
    QLabel *m_label;
};

#endif // WIDGET_H
