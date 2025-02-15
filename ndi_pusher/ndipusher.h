#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QMainWindow>

class infoDialog;
class CenterWidget;
class TitleBar;
class NdiPusher : public QWidget
{
    Q_OBJECT

public:
    explicit NdiPusher(QWidget *parent = 0);
    ~NdiPusher();
    void InitTitleBar();
    void InitCenterWidget();
    void setNdiLayout();

protected:
    virtual void paintEvent ( QPaintEvent * e );  //绘制边框及背景
private slots:
    void slot_info_show();
private:
    infoDialog * m_infoDlg;
    TitleBar * m_titleBar;
    CenterWidget * m_centerWidget;
};

#endif // WIDGET_H
