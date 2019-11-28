#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>

//namespace Ui {
//class CenterWidget;
//}

class QLabel;
class IPAddressEdit;
class QLineEdit;
class QPushButton;
class QListView;
class CenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = 0);
    ~CenterWidget();
    void InitUi();

//private slots:
//    void on_bt_start_push_clicked();

//    void on_bt_end_push_clicked();

//    void on_bt_info_clicked();

//    void on_bt_exit_clicked();

signals:
    void signal_exit();

    void signal_info_show();
private:
//    Ui::CenterWidget *ui;

    QLabel * m_lb_ip_addr;
    QLabel * m_lb_play_buffers;
    QLabel * m_lb_mesc;

    QLabel * m_lb_ip_port;
    QLabel * m_lb_NDI;

    QLabel * m_lb_ip_accept;
    QLabel * m_lb_decode;

    IPAddressEdit * m_ip_addr;
    IPAddressEdit * m_ip_accept;

    QLineEdit * m_line_play_buffer;
    QLineEdit * m_line_ip_port;
    QLineEdit * m_line_NDI;
    QLineEdit * m_line_decode;

    QPushButton * m_bt_start_push;
    QPushButton * m_bt_stop_push;
    QPushButton * m_bt_info;
    QPushButton * m_bt_exit;


    QListView * m_list_view;
};

#endif // CENTERWIDGET_H
