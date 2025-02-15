/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-27
** @version:
*******************************************************************************/

#include <QCoreApplication>
#include "context.h"
#include "concrete_strategy.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) {if(p){delete(p);(p)=NULL;}}
#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IStrategy *bike = new BikeStrategy();
    Context *bikeContext = new Context(bike);

    IStrategy *car = new CarStrategy();
    Context *carContext = new Context(car);

    IStrategy *train = new TrainStrategy();
    Context *trainContext = new Context(train);

    bikeContext->Travel();
    carContext->Travel();
    trainContext->Travel();

    SAFE_DELETE(bike);
    SAFE_DELETE(bikeContext);

    SAFE_DELETE(car);
    SAFE_DELETE(carContext);

    SAFE_DELETE(train);
    SAFE_DELETE(trainContext);

    return a.exec();
}
