/*******************************************************************************
** @file:     strategy.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

#ifndef STRATEGY_H
#define STRATEGY_H

// 创建抽象策略
// 出行策略
#include <iostream>
class IStrategy
{
  public:
    IStrategy(){}
    virtual ~IStrategy()
    {
        std::cout << "Destroy IStrategy." << std::endl;
    }
    virtual void Travel() = 0;
};
#endif // STRATEGY_H
