/*******************************************************************************
** @file:     main.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-4-19
** @version:
*******************************************************************************/

#include "CheckNetWork.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckNetWork w;
    w.show();

    return a.exec();
}
