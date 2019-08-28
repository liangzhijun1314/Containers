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

#endif // LEAF_H
