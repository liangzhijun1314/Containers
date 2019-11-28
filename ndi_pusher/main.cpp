#include "ndipusher.h"
#include <QApplication>
#include "commonhelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommonHelper::setStyle(":/qss/Black");
    NdiPusher w;
    w.show();

    return a.exec();
}
