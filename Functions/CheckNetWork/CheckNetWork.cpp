/*******************************************************************************
** @file:     CheckNetWork.cpp
** @class:
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-4-19
** @version:
*******************************************************************************/

#include "CheckNetWork.h"
#include <QNetworkConfigurationManager>
#include <QHostInfo>
#include <QTimer>
#include <QDebug>

CheckNetWork::CheckNetWork(QWidget *parent)
    : QDialog(parent)
{
    m_message_Object = new QNetworkConfigurationManager(this);
    m_hostInfo = new QHostInfo;

    QList<QNetworkConfiguration> activeConfigs = m_message_Object->allConfigurations(QNetworkConfiguration::Active);
    if (activeConfigs.count() > 0)
        qDebug() << " CheckNetWork : "<< m_message_Object->isOnline();
    else
        qDebug() << " CheckNetWork : "<< !m_message_Object->isOnline();
    QObject::connect(m_message_Object,SIGNAL(onlineStateChanged(bool)),this,SLOT(onlineStateChangedSlot(bool)));

    m_pTimer = new QTimer();
    m_pTimer->setInterval(3 * 1000);
    QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(hostCheck()));
    m_pTimer->start();


}

CheckNetWork::~CheckNetWork()
{

}

void CheckNetWork::hostCheck()
{

    if(isHaveNetWork())
        qDebug()<<"isHaveNetWork is true";
    else
        qDebug()<<"isHaveNetWork is false";

//    m_hostInfo->lookupHost("www.baidu.com", this, SLOT(lookedUp(QHostInfo)));
}

void CheckNetWork::onlineStateChangedSlot(bool isOnline)
{
    qDebug() << " onlineStateChanged : "<< isOnline;
}

void CheckNetWork::lookedUp(const QHostInfo &host)
{
    if(host.error() != QHostInfo::NoError)
    {
        qDebug() << "offline";
        m_errTimes++;
    }
    else
    {
        qDebug() << host.addresses().first().toString();
        qDebug() << "online";
        m_errTimes = 0;
    }
    if(m_errTimes > 20)
    {
        qDebug() << "timeout";
    }
}

