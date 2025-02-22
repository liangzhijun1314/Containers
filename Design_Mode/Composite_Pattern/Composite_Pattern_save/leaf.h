/*******************************************************************************
** @file:     leaf.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

#ifndef LEAF_H
#define LEAF_H

#include "component.h"

// 创建叶子构件
class Leaf : public Component
{
public:
    Leaf(string name) : Component(name){}
    virtual ~Leaf(){}
    void Operation(int indent) {
        string newStr(indent, '-');
        std::cout << newStr << " " << m_strName <<std::endl;
    }

private:
    Leaf();  // 不允许
};

//与透明模式不同，这里已经没有了访问及管理子构件的接口，所有的接口都在 Composite 中
#endif // LEAF_H
