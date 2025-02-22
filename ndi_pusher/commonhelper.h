#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QFile>
#include <QApplication>

#define BUTTON_STYLESHEET(class_name,image_url) (#class_name"{border-image: url("#image_url"_n)}" \
    #class_name":hover{border-image: url("#image_url"_h)}" \
    #class_name":pressed{border-image: url("#image_url"_c)}" \
    #class_name":disabled{border-image: url("#image_url"_n)}")

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

#endif // COMMONHELPER_H
