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

/*
Component:抽象基类，为组合中的对象声明接口,声明了类共有接口的缺省行为(如这里的Add,Remove,GetChild函数),
声明一个接口函数可以访问Component的子组件.
*/
class Component
{
public:
    Component(std::string name) : m_strName(name) {}
    virtual ~Component() {}

    // 虚函数,提供接口,有默认的实现就是什么都不做
    virtual void Add(Component *cmpt) = 0;  // 添加构件
    virtual void Remove(Component *cmpt) = 0;  // 删除构件
    virtual Component* GetChild(int index) = 0;  // 获取构件

    //纯虚函数，只提供接口，没有默认的实现
    virtual void Operation(int indent) = 0;  // 显示构件（以缩进的方式）

private:
    Component();  // 不允许

protected:
    std::string m_strName;
};

#endif // COMPONENT_H
