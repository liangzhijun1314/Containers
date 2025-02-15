/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

// 透明组合模式
#include <QCoreApplication>
#include <iostream>
#include "composite.h"
#include "leaf.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建一个树形结构
    // 创建根节点
    Component * pRoot = new Composite("IRoot");

//    // 创建分支
    Component *pDepart1 = new Composite("A");
    pDepart1->Add(new Leaf("A-child1"));
    pDepart1->Add(new Leaf("A-child2"));
    pRoot->Add(pDepart1);

    Component *pDepart2 = new Composite("B");
    pDepart2->Add(new Leaf("B-child1"));
    pDepart2->Add(new Leaf("B-child2"));
    pDepart2->Add(new Leaf("B-child3"));
    pDepart2->Add(new Leaf("B-child4"));
    pDepart2->Add(new Leaf("B-child5"));
    pRoot->Add(pDepart2);

    // 添加和删除叶子
    pRoot->Add(new Leaf("C"));
    pRoot->Add(new Leaf("D"));
    Component *pLeaf = new Leaf("E");
    pRoot->Add(pLeaf);

    // 小丑，直接裁掉
    pRoot->Remove(pLeaf);

    // 递归地显示组织架构
    pRoot->Operation(1);

    // 删除分配的内存
    SAFE_DELETE(pRoot);

    getchar();

    return a.exec();
}
