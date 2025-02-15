/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-7-23
** @version:
*******************************************************************************/

#include <QCoreApplication>
#include "singletonobj.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SingletonObject * obj = SingletonObject::instance();
    obj->DoTest();
    obj->freeinstance();


    return a.exec();
}
