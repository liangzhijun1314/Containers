/*******************************************************************************
** @file:     context.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

#ifndef CONTEXT_H
#define CONTEXT_H

#include "strategy.h"
#include <iostream>

// 创建环境角色
// 环境角色对外提供了一个 Travel() 接口，最终由客户端调用。在内部，它最终调用的是 IStrategy 的相应方法：
class Context
{
public:
    Context(IStrategy *strategy)
    {
        m_pStrategy = strategy;
    }
    void Travel()
    {
        m_pStrategy->Travel();
    }

    ~Context()
    {
//        if(m_pStrategy)
//            delete m_pStrategy;

        std::cout << "Destroy context." << std::endl;
    }
private:
    IStrategy *m_pStrategy;
};

#endif // CONTEXT_H
