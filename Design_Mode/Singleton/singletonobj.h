/*******************************************************************************
** @file:     singletonobj.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-7-23
** @version:
*******************************************************************************/

#ifndef SINGLETONOBJ_H
#define SINGLETONOBJ_H

#include "singleton.h"
#include <QDebug>

class SingletonObject
{
    DECLARE_SINGLETON(SingletonObject);
private:
    SingletonObject(){}
    ~SingletonObject(){}
public:
    void DoTest()
    {
        qDebug()<< "Test...";
    }
};
#endif // SINGLETONOBJ_H
