/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-1-24
** @version:
*******************************************************************************/

#include <QCoreApplication>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <QList>
#include <WinSock2.h>
#include <iphlpapi.h>
#include <QList>

QString getHostMacAddress() {
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        qDebug()<<"trimmed = " << nets[i].humanReadableName().trimmed();
        qDebug()<<"humanReadableName = " << nets[i].humanReadableName();
        qDebug()<<"hardwareAddress = " << nets[i].hardwareAddress();

        QList<QNetworkInterface> interFace = nets[i].allInterfaces();

        foreach(QNetworkInterface netInterface, interFace) {

            //设备名
            qDebug() << "Device:" << netInterface.name();

            //MAC地址
            qDebug() << "HardwareAddress:" << netInterface.hardwareAddress();

//            QList entryList = netInterface.addressEntries();

//            //遍历每一个IP地址(每个包含一个IP地址，一个子网掩码和一个广播地址)
//            foreach(QNetworkAddressEntry entry, entryList)
//            {
//                //IP地址
//                qDebug() << "IP Address:" << entry.ip().toString();

//                //子网掩码
//                qDebug() << "Netmask:" << entry.netmask().toString();

//                //广播地址
//                qDebug() << "Broadcast:" << entry.broadcast().toString();
//            }
        }




//        if (nets[i].humanReadableName().trimmed() == "本地连接 2")
//            continue;
//        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
//        if(nets[i].flags().testFlag(QNetworkInterface::IsUp)
//                && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
//                && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
//        {
//            strMacAddr = nets[i].hardwareAddress();
//            break;
//        }
    }
    return strMacAddr;
}

QString GetLocalIP()
{
//    QList<QHostAddress> list = QNetworkInterface::allAddresses();

//    foreach(QHostAddress address, list)
//    {
//        if (address.protocol() == QAbstractSocket::IPv4Protocol)
//            return address.toString();
//    }
//    return "";

    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        qDebug()<<QString("iplist at %1 ").arg(QString::number(i)) << ipAddressesList.at(i).toString();
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return strIpAddress;
}

QStringList get_mac_list()
{
    QStringList mac_list;
    QString strMac;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i=0; i<ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        //过滤掉本地回环地址、没有开启的地址
        if (iface.flags().testFlag(QNetworkInterface::IsUp) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            //过滤掉虚拟地址
            if (!(iface.humanReadableName().contains("VMware",Qt::CaseInsensitive)))
            {
                strMac = iface.hardwareAddress();
                mac_list.append(strMac);
            }
        }
    }
    return mac_list;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString localIp = GetLocalIP();
    qDebug()<<"localIp = " << localIp;

    QString macAddress1 = getHostMacAddress();
    qDebug()<<"macAddress 1= " << macAddress1;

    QStringList macAddList = get_mac_list();
    for (int i = 0; i < macAddList.size(); i++) {
        qDebug()<<QString("mac list %1 : ").arg(QString::number(i)) << macAddList.at(i);
    }
    return a.exec();
}
