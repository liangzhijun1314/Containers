#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>

class QLabel;
class IPAddressEdit;
class QLineEdit;
class QPushButton;
class QListView;
class QTextBrowser;
class QListWidget;
class CenterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenterWidget(QWidget *parent = 0);
    ~CenterWidget();
    void initUi();
    void initLogger();
    void destroyLogger();
    void setBtnEnable(bool isStart);

public slots:
    void on_bt_start_push_clicked();

    void on_bt_stop_push_clicked();

    void on_bt_info_clicked();

    void on_bt_exit_clicked();

    void logSlot(const QString &message, int level);

signals:
    void signal_exit();

    void signal_info_show();
private:

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
    QTextBrowser * m_textBrowser;
    QListWidget * m_listWidget;

    long m_row;

};

#endif // CENTERWIDGET_H
