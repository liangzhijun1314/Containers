/*******************************************************************************
** @file:     mainwindow.h
** @class:    MainWindow
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-2
** @version:
*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
