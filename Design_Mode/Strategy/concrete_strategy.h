/*******************************************************************************
** @file:     concrete_strategy.h
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-28
** @version:
*******************************************************************************/

#ifndef CONCRETE_STRATEGY_H
#define CONCRETE_STRATEGY_H

#include "strategy.h"
#include <iostream>

// 创建具体策略
// 有三种具体的策略可供选择，骑自行车、开车、坐火车

// 自行车类
class BikeStrategy : public IStrategy
{
public:
    BikeStrategy(){}
    virtual ~BikeStrategy()
    {
        std::cout << "Destroy BikeStrategy." << std::endl;
    }
    virtual void Travel() override
    {
        std::cout << "Travel by bike." << std::endl;
    }
};

// 开车
class CarStrategy : public IStrategy
{
public:
    CarStrategy(){}
    virtual ~CarStrategy()
    {
        std::cout << "Destroy CarStrategy." << std::endl;
    }
    virtual void Travel() override
    {
        std::cout << "Travel by car." << std::endl;
    }
};

// 火车
class TrainStrategy  : public IStrategy
{
public:
    TrainStrategy(){}
    virtual ~TrainStrategy()
    {
        std::cout << "Destroy TrainStrategy." << std::endl;
    }
    virtual void Travel() override
    {
        std::cout << "Travel by train." << std::endl;
    }
};


#endif // CONCRETE_STRATEGY_H
