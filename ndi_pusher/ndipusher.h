#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QMainWindow>

class infoDialog;
class CenterWidget;
class NdiPusher : public QWidget
{
    Q_OBJECT

public:
    explicit NdiPusher(QWidget *parent = 0);
    ~NdiPusher();
    void InitTitleBar();
    void InitCenterWidget();

private slots:
    void slot_info_show();
private:
    infoDialog * m_infoDlg;
    CenterWidget * m_centerWidget;
};

#endif // WIDGET_H
