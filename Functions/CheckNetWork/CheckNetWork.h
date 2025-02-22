/*******************************************************************************
** @file:     CheckNetWork.h
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-4-19
** @version:
*******************************************************************************/

#ifndef CHECKNETWORK_H
#define CHECKNETWORK_H

#include <QDialog>
#include <QNetworkConfigurationManager>
#include <QHostInfo>
#include <QTcpSocket>
#include <QTimer>

class CheckNetWork : public QDialog
{
    Q_OBJECT

public:
    CheckNetWork(QWidget *parent = 0);
    ~CheckNetWork();

    //判断IP地址及端口是否在线
    static bool Ping(QString url, int port, int timeout = 5000) {
        QTcpSocket tcpClient;
        tcpClient.abort();
        tcpClient.connectToHost(url, port);
        //100毫秒没有连接上则判断不在线
        return tcpClient.waitForConnected(timeout);
    }
    //判断是否通外网
    static bool isHaveNetWork() {
        //能接通百度IP说明可以通外网
        return Ping("www.baidu.com", 80);
    }

public slots:
    void onlineStateChangedSlot(bool isonline);

    void hostCheck();
    void lookedUp(const QHostInfo &host);
private:
    QNetworkConfigurationManager* m_message_Object;
    QHostInfo * m_hostInfo;
    int     m_errTimes = 0;
    QTimer  *m_pTimer;
};

#endif // CHECKNETWORK_H
