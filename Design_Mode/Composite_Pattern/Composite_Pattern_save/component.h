/*******************************************************************************
** @file:     component.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>

using namespace std;

// 创建抽象构件
class Component
{
public:
    Component(string name) : m_strName(name) {}
    virtual ~Component() {}
    virtual void Operation(int indent) = 0;  // 显示构件（以缩进的方式）

private:
    Component();  // 不允许

protected:
    string m_strName;
};

#endif // COMPONENT_H
