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

// 作为 Component 的子类，Leaf 需要实现 Component 中定义的所有接口，但是 Leaf 不能包含子构件。
// 因此，在 Leaf 中实现访问和管理子构件的函数时，需要进行异常处理或错误提示
// Leaf是叶子结点,也就是不含有子组件的结点类，所以不用实现Add、Remove、GetChild等方法
class Leaf : public Component
{
public:
    Leaf(std::string name) : Component(name){}
    virtual ~Leaf(){}
    void Add(Component *cmpt) {
        cout << "Can't add to a Leaf" << endl;
    }
    void Remove(Component *cmpt) {
        cout << "Can't remove from a Leaf" << endl;
    }
    Component* GetChild(int index) {
        cout << "Can't get child from a Leaf" << endl;
        return NULL;
    }
    void Operation(int indent) {
        string newStr(indent, '-');
        cout << newStr << " " << m_strName <<endl;
    }

private:
    Leaf();  // 不允许
};

#endif // LEAF_H
