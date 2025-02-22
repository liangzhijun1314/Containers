#include "centerwidget.h"
#include <QLabel>
#include "IPAddressEdit.h"
#include <QLayout>
#include <QLineEdit>
#include <QListView>
#include <QTextBrowser>
#include <QListWidget>
#include <QPushButton>
#include <QDebug>

#include "QsLog.h"
#include "QsLogDest.h"
#include <QCoreApplication>
#include <QDir>

using namespace QsLogging;

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setObjectName("centerWidget");
    initUi();
    initLogger();
}

CenterWidget::~CenterWidget()
{
    destroyLogger();
}

void CenterWidget::initUi()
{
    QFont font;
    font.setBold(true);
    //font.setWeight(75);
    m_lb_ip_addr = new QLabel(this);
    m_lb_ip_addr->setText("IP 地址");
    m_lb_ip_addr->setFont(font);
    m_lb_ip_addr->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_ip_addr = new IPAddressEdit(this);
    m_ip_addr->setIP("233.1.0.1");
    m_ip_addr->setMaximumWidth(140);
    m_ip_addr->setMaximumHeight(20);

    m_lb_play_buffers = new QLabel(this);
    m_lb_play_buffers->setText("播放缓冲");
    m_lb_play_buffers->setFont(font);
    m_lb_play_buffers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_line_play_buffer = new QLineEdit(this);
    m_line_play_buffer->setText("40");
    m_line_play_buffer->setMaximumWidth(140);

    m_lb_mesc = new QLabel(this);
    m_lb_mesc->setText("毫秒");
    m_lb_mesc->setAlignment(Qt::AlignLeft|Qt::AlignTrailing|Qt::AlignVCenter);

    m_bt_start_push = new QPushButton(this);
    m_bt_start_push->setFont(font);
    m_bt_start_push->setText("Start Push");
    m_bt_start_push->setMinimumSize(80,30);

    //--------------
    m_lb_ip_port = new QLabel(this);
    m_lb_ip_port->setText("IP 端口");
    m_lb_ip_port->setFont(font);
    m_lb_ip_port->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_line_ip_port = new QLineEdit(this);
    m_line_ip_port->setText("1234");
    m_line_ip_port->setMaximumWidth(140);

    m_lb_NDI = new QLabel(this);
    m_lb_NDI->setText("NDI 名称");
    m_lb_NDI->setFont(font);
    m_lb_NDI->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_line_NDI = new QLineEdit(this);
    m_line_NDI->setText("NDI测试推流");
    m_line_NDI->setMaximumWidth(140);

    m_bt_stop_push = new QPushButton(this);
    m_bt_stop_push->setFont(font);
    m_bt_stop_push->setText("Stop Push");
    m_bt_stop_push->setEnabled(false);

    m_bt_exit = new QPushButton(this);
    m_bt_exit->setFont(font);
    m_bt_exit->setText("Exit");

    //-----
    m_lb_ip_accept = new QLabel(this);
    m_lb_ip_accept->setText("收流 IP");
    m_lb_ip_accept->setFont(font);
    m_lb_ip_accept->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_ip_accept = new IPAddressEdit(this);
    m_ip_accept->setIP("0.0.0.0");
    m_ip_accept->setMaximumWidth(140);
    m_ip_accept->setMaximumHeight(20);

    m_lb_decode = new QLabel(this);
    m_lb_decode->setText("解码线程");
    m_lb_decode->setFont(font);
    m_lb_decode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    m_line_decode = new QLineEdit(this);
    m_line_decode->setText("4");
    m_line_decode->setMaximumWidth(140);

    m_bt_info = new QPushButton("统计信息 ",this);
    m_bt_info->setEnabled(false);
    m_bt_info->setFont(font);

    //-----
    QGridLayout *gLayout1 = new QGridLayout();
    gLayout1->addWidget(m_lb_ip_addr,0,0);
    gLayout1->addWidget(m_ip_addr,0,1);
    gLayout1->addWidget(m_lb_ip_port,1,0);
    gLayout1->addWidget(m_line_ip_port,1,1);
    gLayout1->addWidget(m_lb_ip_accept,2,0);
    gLayout1->addWidget(m_ip_accept,2,1);


    QGridLayout * gLayout2 = new QGridLayout();
    gLayout2->addWidget(m_lb_play_buffers,0,0);
    gLayout2->addWidget(m_line_play_buffer,0,1);
    gLayout2->addWidget(m_lb_mesc,0,2);
    gLayout2->addWidget(m_lb_NDI,1,0);
    gLayout2->addWidget(m_line_NDI,1,1);
    gLayout2->addWidget(m_lb_decode,2,0);
    gLayout2->addWidget(m_line_decode,2,1);


    QGridLayout * gLayout3 = new QGridLayout();
    gLayout3->addWidget(m_bt_start_push,0,0);
    gLayout3->addWidget(m_bt_stop_push,1,0);
    gLayout3->addWidget(m_bt_exit,1,1);
    gLayout3->addWidget(m_bt_info,2,0);

    QHBoxLayout *hLayout = new QHBoxLayout();
    //hLayout->addStretch();
    hLayout->addLayout(gLayout1);
    hLayout->addStretch();
    hLayout->addLayout(gLayout2);
    hLayout->addStretch();
    hLayout->addLayout(gLayout3);
    //hLayout->addStretch();
    hLayout->setMargin(9);
   //----------
    //m_list_view = new QListView(this);
    m_textBrowser = new QTextBrowser(this);
    m_textBrowser->setObjectName("textBrowser");
    //m_listWidget = new QListWidget(this);

    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_textBrowser);
    vLayout->setStretch(0, 2);
    vLayout->setStretch(1, 8);
    vLayout->setMargin(6);
    setLayout(vLayout);

    connect(m_bt_start_push,SIGNAL(clicked(bool)),this,SLOT(on_bt_start_push_clicked()));
    connect(m_bt_stop_push,SIGNAL(clicked(bool)),this,SLOT(on_bt_stop_push_clicked()));
    connect(m_bt_info,SIGNAL(clicked(bool)),this,SLOT(on_bt_info_clicked()));
    connect(m_bt_exit,SIGNAL(clicked(bool)),this,SLOT(on_bt_exit_clicked()));

}

void CenterWidget::initLogger()
{
    m_row = 0;
    // 1. init the logging mechanism
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    //设置log位置
    const QString sLogPath(QDir(QCoreApplication::applicationDirPath()).filePath("log.txt"));

    // 2. add two destinations
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                       sLogPath, EnableLogRotation, MaxSizeBytes(512), MaxOldLogCount(2)));
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    //DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));

    //这样和槽函数连接
    DestinationPtr sigsSlotDestination(DestinationFactory::MakeFunctorDestination(this, SLOT(logSlot(QString,int))));

    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
    //logger.addDestination(functorDestination);
    logger.addDestination(sigsSlotDestination);

    // 3. start logging
    QLOG_INFO() << "Program started";
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();

    QLOG_TRACE() << "Here's a" << QString::fromUtf8("trace") << "message";
    QLOG_DEBUG() << "Here's a" << static_cast<int>(QsLogging::DebugLevel) << "message";
    QLOG_WARN()  << "Uh-oh!";
    qDebug() << "This message won't be picked up by the logger";
    QLOG_ERROR() << "An err has occurred";
    qWarning() << "Neither will this one";
    QLOG_FATAL() << "Fatal error!";

}

void CenterWidget::logSlot(const QString &message, int level)
{
    // QTextBrowser
    if(level >= 4) {
        m_textBrowser->append("<font color=\"#FF0000\">" + message + "</font> ");
        /* 加上颜色显示之后，\n就没了。。。这里加上 */
        if(message[message.length()-1] == '\n')
        {
             m_textBrowser->append("\n");
        }
    } else {
        m_textBrowser->append(qPrintable(message));
    }
    // QListWidget
    //    m_listWidget->insertItem(m_row, qPrintable(message));
    //    m_row++;
}

void CenterWidget::destroyLogger()
{
    QsLogging::Logger::destroyInstance();
}

void CenterWidget::setBtnEnable(bool isStart)
{
    m_bt_stop_push->setEnabled(isStart);
    m_bt_info->setEnabled(isStart);
    m_bt_exit->setEnabled(!isStart);
    m_bt_start_push->setEnabled(!isStart);
}

void CenterWidget::on_bt_start_push_clicked()
{
    QLOG_INFO() << "Start push stream ok, IP : " << m_ip_addr->getIP();
    setBtnEnable(true);
}

void CenterWidget::on_bt_stop_push_clicked()
{
    QLOG_INFO() << "Stop push stream ok.";
    setBtnEnable(false);
}

void CenterWidget::on_bt_info_clicked()
{
    emit signal_info_show();
}

void CenterWidget::on_bt_exit_clicked()
{
    emit signal_exit();
}

